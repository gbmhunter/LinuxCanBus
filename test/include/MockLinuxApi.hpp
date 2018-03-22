
// 3rd party includes
#include <gmock/gmock.h>

// Local includes
#include "LinuxCanBus/ILinuxApi.hpp"

namespace mn {
    namespace LinuxCanBus {
        class MockLinuxApi : public ILinuxApi {
        public:

            MOCK_METHOD3(socket_, int(int domain, int type, int protocol));
            MOCK_METHOD1(close_, int(int fd));

            MOCK_METHOD3(fcntl_, int(int fd, int cmd, int openMode));
            MOCK_METHOD3(ioctl_, int(int fd, unsigned long request, ifreq* ifr));

            MOCK_METHOD3(read_, ssize_t(int fd, void *buf, size_t count));
            MOCK_METHOD3(write_, ssize_t(int fd, const void *buf, size_t count));
            MOCK_METHOD5(select_, int(int nfds, fd_set *readfds, fd_set *writefds,
                    fd_set *exceptfds, struct timeval *timeout));


            MOCK_METHOD3(bind_, int(int sockfd, const struct sockaddr *addr, socklen_t addrlen));
        };
    }
}

