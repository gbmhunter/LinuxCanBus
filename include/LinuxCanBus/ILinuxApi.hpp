// Forward declarations
//class size_t;
//class ssize_t;
//class fd_set;

// Header guard
#ifndef MN_LINUX_CAN_BUS_I_LINUX_API_H_
#define MN_LINUX_CAN_BUS_I_LINUX_API_H_

namespace mn {
    namespace LinuxCanBus {

        /// \brief      Interface to Linux API used with socket CAN.
        /// \details    Interface created so can be replaced with mocks for unit
        ///                 testing. #LinuxApiReal forwards these calls onto the actual
        ///                 Linux functions.
        class ILinuxApi {

        public:
            virtual ssize_t read_(int fd, void *buf, size_t count) = 0;

            virtual ssize_t write_(int fd, const void *buf, size_t count) = 0;

            virtual int select_(int nfds, fd_set *readfds, fd_set *writefds,
                       fd_set *exceptfds, struct timeval *timeout) = 0;

            /// \details    fcntl is a varidac function, a since no vargs version exists
            ///             (i.e. fcntl), we have to specialize here for our needs (1 extra param).
            virtual int fcntl_(int fd, int cmd, int openMode) = 0;

            virtual int bind_(int sockfd, const struct sockaddr *addr,
                     socklen_t addrlen) = 0;

        };

    }
}

#endif // #ifndef MN_LINUX_CAN_BUS_I_LINUX_API_H_