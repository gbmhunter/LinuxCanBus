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
        ///             testing.
        class ILinuxApi {

        public:
            virtual ssize_t Read(int fd, void *buf, size_t count) = 0;
            virtual int Select(int nfds, fd_set *readfds, fd_set *writefds,
                       fd_set *exceptfds, struct timeval *timeout) = 0;

        };

    }
}

#endif // #ifndef MN_LINUX_CAN_BUS_I_LINUX_API_H_