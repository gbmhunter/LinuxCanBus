///
/// \file               LinuxCanBus.hpp
/// \author             Geoffrey Hunter (www.mbedded.ninja) <gbmhunter@gmail.com>
/// \edited             n/a
/// \created            2018-03-21
/// \last-modified      2018-03-21
/// \brief              Contains the LinuxCanBus class.
/// \details
///		See README in root dir for more info.

// Header guard
#ifndef MN_LINUX_CAN_BUS_LINUX_CAN_BUS_H_
#define MN_LINUX_CAN_BUS_LINUX_CAN_BUS_H_

// stdlib includes
#include <memory>
#include <mutex>

// Linux includes
#include <linux/can/raw.h>
#include <net/if.h>

// Local includes
#include "LinuxCanBus/CanMsg.hpp"
#include "LinuxCanBus/ILinuxApi.hpp"
#include "LinuxCanBus/LinuxApiReal.hpp"



namespace mn {
    namespace LinuxCanBus {


        class LinuxCanBus {

        public:

            enum class FrameFormat {
                STANDARD,
                EXTENDED
            };

            enum class State {
                CLOSED,
                OPEN
            };

            enum class ReturnCode {
                RECEIVED_MSG, // GetMessage()
                TIMEOUT // GetMessage()
            };

            LinuxCanBus();


            /// \brief      Initialises the CAN bus interface.
            /// \param      interfaceName   The name of the CAN interface you want to connect to (e.g. 'can0', 'vcan3').
            /// \param      bitRate             The bit rate of the CAN interface.
            /// \param      frameType       The frame type you wish to use with the CAN bus interface.
            void Init(const std::string &interfaceName, FrameFormat frameFormat);

            void SetLinuxApi(std::shared_ptr<ILinuxApi> linuxApi);

            /// \brief      Call to open the CAN bus (i.e. start).
            /// \details    Creates a socket and binds it to the SocketCAN interface.
            /// \throws     LinuxCanBusException
            void Open();

            /// \brief      Call to close the CAN bus (i.e. stop).
            /// \details    Closes the Linux socket. Does nothing if CAN bus is not open.
            void Close();

            /// \brief      Call to read a msg received on the CAN bus (RX).
            /// \details    Reads one message from the CAN bus. Blocks until message is available, or until
            ///             non-zero timeout expires.
            /// \param      canMsg      The CAN msg object to write the received message to. Will clear existing data,
            ///                         even if timeout occurs.
            /// \returns    RECEIVED_MSG if CAN message was received (and canMsg is now valid),
            ///                 TIMEOUT if timeout occurred before a message was received.
            /// \warning    Blocking method (but with timeout).
            /// \warning    Is not thread-safe OR reentrant.
            /// \throws
            virtual ReturnCode Read(CanMsg &canMsg, uint32_t timeout_ms);

            /// \brief      Call to write a message to the CAN bus.
            /// \note       Re-entrant and thread-safe.
            /// \warning    Blocking method.
            virtual void Write(const CanMsg &canMsg);

            std::string GetInterfaceName() const;

            FrameFormat GetFrameFormat() const;

            State GetState() const;


        private:

            std::shared_ptr<ILinuxApi> linuxApi_;

            std::string interfaceName_;

            /// \brief      Keeps track of whether the CAN interface has been started
            ///             via can_do_start().
            bool canInterfaceUp_;

            State state_;

            FrameFormat frameFormat_;

            int socketFd_;            

            struct ifreq ifr_;
            struct sockaddr_can addr_;

//            std::mutex writeSysCallMutex_;

            static constexpr uint8_t CAN_ID_11_BIT_ADD_START_POS = 0;   ///< Bits [0:10]
            static constexpr uint8_t CAN_ID_18_BIT_ADD_START_POS = 11;  ///< Bits [11:28]
            static constexpr uint8_t CAN_ID_FRAME_FORMAT_BIT_POS = 31;  ///< Bits [31]


        };
    }
}

#endif // #ifndef MN_LINUX_CAN_BUS_LINUX_CAN_BUS_H_