///
/// \file               LinuxCanBus.cpp
/// \author             Geoffrey Hunter (www.mbedded.ninja) <gbmhunter@gmail.com>
/// \edited             n/a
/// \created            2018-03-21
/// \last-modified      2018-03-21
/// \brief              Contains the LinuxCanBus class.
/// \details
///		See README in root dir for more info.

// stdlib includes
#include <iostream>
#include <cstring>

// Linux includes
#include <fcntl.h>
#include <linux/can/raw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

// Local includes
#include "LinuxCanBus/Bits.hpp"
#include "LinuxCanBus/LinuxCanBus.hpp"

namespace mn {
    namespace LinuxCanBus {

        LinuxCanBus::LinuxCanBus() :
            state_(State::CLOSED) {}

        void LinuxCanBus::Init(ILinuxApi* linuxApi, const std::string &interfaceName, int bitRate, FrameFormat frameFormat) {
            std::cout << "Init() called." << std::endl;

            linuxApi_ = linuxApi;

            interfaceName_ = interfaceName;
            bitRate_ = bitRate;
            frameFormat_ = frameFormat;
        }

        void LinuxCanBus::Open() {

            // Open a CAN_RAW socket
            socketFd_ = linuxApi_->socket_(PF_CAN, SOCK_RAW, CAN_RAW);
            if (socketFd_ < 0) {
                throw std::runtime_error("socketFd_ < 0");
            }
            addr_.can_family = AF_CAN;

            // Copy the provided interface name into the ifr structure
            strcpy(ifr_.ifr_name, interfaceName_.c_str());

            // ioctl() can return -1 if interface name is invalid
            if (linuxApi_->ioctl_(socketFd_, SIOCGIFINDEX, &ifr_) < 0)
                throw std::runtime_error("\"" + interfaceName_ + "\" is an invalid interface name.");

            // Setup address for bind
            addr_.can_ifindex = ifr_.ifr_ifindex;

            linuxApi_->fcntl_(socketFd_, F_SETFL, O_NONBLOCK);
            if (linuxApi_->bind_(socketFd_, (struct sockaddr *) &addr_, sizeof(addr_)) < 0) {
                throw std::runtime_error("bind < 0");
            }

            // If we make it here, we are now running
            state_ = State::OPEN;

        }

        void LinuxCanBus::Close() {
            if (socketFd_ >= 0) {

                // Don't care if close() returns -1, there
                // is not much we can do about it anyway
                linuxApi_->close_(socketFd_);

                socketFd_ = -1;
            }

            state_ = State::CLOSED;
        }

        LinuxCanBus::ReturnCode LinuxCanBus::Read(CanMsg &canMsg, uint32_t timeout_ms) {
            //LOG((*logger_), DEBUG, "Method called.");

            // Clear any existing data in canMsg
            canMsg.ClearAll();

            // Convert timeout in milliseconds to the seconds/microseconds format
            // required by the socket() call
            uint32_t seconds = timeout_ms / 1000; // Truncate towards zero
            uint32_t microseconds =
                    (timeout_ms - seconds * 1000) * 1000; // Get remainder from previous calc and convert to us
            struct timeval timeout = {seconds, microseconds};

            // Create a set
            fd_set readSet;

            // Zero the set
            FD_ZERO(&readSet);

            // Add file descriptor to set
            FD_SET(socketFd_, &readSet);

            // select() returns once it is possible to call read() without
            // blocking. No write set or except set. soc + 1 is ndfs variable
            // which has to be highest file descriptor + 1.
            int retVal = linuxApi_->select_((socketFd_ + 1), &readSet, NULL, NULL, &timeout);


            if (retVal == 1) {

                // Check if file descriptor is part of set. This is a sanity
                // check, as this should always return true if the above socket()
                // call returned 1
                if (FD_ISSET(socketFd_, &readSet)) {
                    std::cout << "Calling read()..." << std::endl;

                    can_frame canFrame;

                    auto numRxBytes = linuxApi_->read_(socketFd_, &canFrame, sizeof(struct can_frame));

                    // read() should always return and state that it wrote to
                    // all bytes in the passed in can_frame
                    if ((size_t) numRxBytes < sizeof(struct can_frame))
                        throw std::runtime_error("Received incomplete CAN frame.");

                    // Convert Linux can_frame into canMsg
//                    canMsg.SetElevenBitId((uint16_t) Util::GetBits(canFrame.can_id, CAN_ID_11_BIT_ADD_START_POS, 11));
//                    canMsg.SetEighteenBitId(Util::GetBits(canFrame.can_id, CAN_ID_18_BIT_ADD_START_POS, 18));
                    canMsg.arbitrationField_.address = (uint32_t) CppUtils::Bits::GetBits(canFrame.can_id, 0, 29);

                    // Make sure the received message frame format bit matches the expected frame format
                    if (CppUtils::Bits::GetBits(canFrame.can_id, CAN_ID_FRAME_FORMAT_BIT_POS, 1) == 0 &&
                        frameFormat_ == FrameFormat::EXTENDED)
                        throw std::runtime_error(
                                "Received standard frame format msg but frame format was set to EXTENDED.");

                    if (CppUtils::Bits::GetBits(canFrame.can_id, CAN_ID_FRAME_FORMAT_BIT_POS, 1) == 1 &&
                        frameFormat_ == FrameFormat::STANDARD)
                        throw std::runtime_error(
                                "Received extended frame format msg but frame format was set to STANDARD.");

                    for (int i = 0; i < canFrame.can_dlc; i++) {
                        canMsg.data_.push_back(canFrame.data[i]);
                    }

                    // We have received a CAN message, return!
                    return ReturnCode::RECEIVED_MSG;
                } else {
                    throw std::runtime_error("FD_ISSET() returned false.");
                }
            } else if (retVal == 0) {
                // This will true if timeout occurred
                return ReturnCode::TIMEOUT;
            } else {
                throw std::runtime_error("select() returned unexpected value.");
            }
        }


        void LinuxCanBus::Write(const CanMsg &canMsg) {
            // Convert ExtendedMsg into Linux can_frame
            can_frame canFrame;
            canFrame.can_id = 0;

            uint32_t elevenBitId = CppUtils::Bits::GetBits(canMsg.arbitrationField_.address, 0, 11);
            uint32_t eighteenBitId = CppUtils::Bits::GetBits(canMsg.arbitrationField_.address, 11, 18);

            canFrame.can_id = CppUtils::Bits::SetBits<uint32_t>(canFrame.can_id, elevenBitId, CAN_ID_11_BIT_ADD_START_POS, 11);

            // Make sure the provided message address matches the expected frame format
            if(eighteenBitId != 0 && frameFormat_ == FrameFormat::STANDARD)
                throw std::runtime_error("PutMessage() provided with extended frame format address but frame format was set to STANDARD.");

            // Set the extended address and frame format bit if required
            if(frameFormat_ == FrameFormat::EXTENDED) {
                canFrame.can_id = CppUtils::Bits::SetBits<uint32_t>(canFrame.can_id, eighteenBitId, CAN_ID_18_BIT_ADD_START_POS, 18);
                canFrame.can_id = CppUtils::Bits::SetBits<uint32_t>(canFrame.can_id, 1, CAN_ID_FRAME_FORMAT_BIT_POS, 1);
            }

            for (size_t i = 0; i < canMsg.data_.size(); i++)
                canFrame.data[i] = canMsg.data_[i];

            // Set the "data length code" to the number of bytes
            canFrame.can_dlc = static_cast<uint8_t>(canMsg.data_.size());

            ssize_t retval;

            // This next line is the only one which has thread-safety concerns,
            // could not find a reliable source which stated whether this is/is not thread
            // safe, so a mutex is used just in case
//            writeSysCallMutex_.lock();
            retval = linuxApi_->write_(socketFd_, &canFrame, sizeof(struct can_frame));
//            writeSysCallMutex_.unlock();

            if (retval != sizeof(struct can_frame)) {
                throw std::runtime_error("retVal (\"" + std::to_string(retval) + "\" != sizeof(can_frame) (\"" +
                                         std::to_string(sizeof(struct can_frame)) + "\")." +
                                         " Is the interface up?");
            }

        }

        std::string LinuxCanBus::GetInterfaceName() const {
            return interfaceName_;
        }

        LinuxCanBus::FrameFormat LinuxCanBus::GetFrameFormat() const {
            return frameFormat_;
        }

        LinuxCanBus::State LinuxCanBus::GetState() const {
            return state_;
        }

    }

}
