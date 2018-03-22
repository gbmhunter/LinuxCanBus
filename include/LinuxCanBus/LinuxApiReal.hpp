// Header guard
#ifndef MN_LINUX_CAN_BUS_LINUX_API_REAL_H_
#define MN_LINUX_CAN_BUS_LINUX_API_REAL_H_

// Linux includes
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <unistd.h>

// Local includes
#include "LinuxCanBus/ILinuxApi.hpp"

// Forward declarations

namespace mn {
    namespace LinuxCanBus {

        /// \brief      Interface to Linux API used with socket CAN.
        /// \details    Interface created so can be replaced with mocks for unit
        ///             testing.
        class LinuxApiReal : public ILinuxApi {

            public:

                int socket_(int domain, int type, int protocol) override {
                    return socket(domain, type, protocol);
                };

                int close_(int fd) override {
                    return close(fd);
                };

                ssize_t read_(int fd, void *buf, size_t count) override {
                    return read(fd, buf, count);
                }

                ssize_t write_(int fd, const void *buf, size_t count) override {
                    return write(fd, buf, count);
                };

                int select_(int nfds, fd_set *readfds, fd_set *writefds,
                                   fd_set *exceptfds, struct timeval *timeout) override {
                    return select(nfds, readfds, writefds, exceptfds, timeout);
                };

                int ioctl_(int fd, unsigned long request, ifreq* ifr) override {
                    return ioctl(fd, request, ifr);
                }

                int fcntl_(int fd, int cmd, int openMode) override {
                    return fcntl(fd, cmd, openMode);
                };

                int bind_(int sockfd, const struct sockaddr *addr, socklen_t addrlen) override {
                    return bind(sockfd, addr, addrlen);
                };

        };

    }
}

#endif // #ifndef MN_LINUX_CAN_BUS_LINUX_API_REAL_H_