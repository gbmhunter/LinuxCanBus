
// stdlib includes
#include <iostream>
#include <cstring>

// Linux includes
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can/raw.h>

// Local includes
#include "LinuxCanBus/LinuxCanBus.hpp"

void LinuxCanBus::Init(const std::string &interfaceName, int bitRate, FrameFormat frameFormat) {
    std::cout << "Init() called." << std::endl;

    interfaceName_ = interfaceName;
    bitRate_ = bitRate;
    frameFormat_ = frameFormat;
}

void LinuxCanBus::Open() {

    // Open a CAN_RAW socket
    socketFd_ = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (socketFd_ < 0) {
        throw std::runtime_error("socketFd_ < 0");
    }
    addr_.can_family = AF_CAN;

    // Copy the provided interface name into the ifr structure
    strcpy(ifr_.ifr_name, interfaceName_.c_str());

    // ioctl() can return -1 if interface name is invalid
    if (ioctl(socketFd_, SIOCGIFINDEX, &ifr_) < 0)
        throw std::runtime_error("\"" + interfaceName_ + "\" is an invalid interface name.");

    // Setup address for bind
    addr_.can_ifindex = ifr_.ifr_ifindex;

    fcntl(socketFd_, F_SETFL, O_NONBLOCK);
    if (bind(socketFd_, (struct sockaddr *) &addr_, sizeof(addr_)) < 0) {
        throw std::runtime_error("bind < 0");
    }

    // If we make it here, we are now running
    state_ = State::RUNNING;

}