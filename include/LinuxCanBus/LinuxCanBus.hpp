// stdlib includes
#include <mutex>

// Linux includes
#include <linux/can/raw.h>
#include <net/if.h>

class LinuxCanBus {

public:

    enum class FrameFormat {
        STANDARD,
        EXTENDED
    };

    enum class State {
        STOPPED,
        RUNNING
    };

    enum class ReturnCode {
        RECEIVED_MSG, // GetMessage()
        TIMEOUT // GetMessage()
    };


    /// \brief      Initialises the CAN bus interface.
    /// \param      interfaceName   The name of the CAN interface you want to connect to (e.g. 'can0', 'vcan3').
/// \param      bitRate             The bit rate of the CAN interface.
    /// \param      frameType       The frame type you wish to use with the CAN bus interface.
    void Init(const std::string &interfaceName, int bitRate, FrameFormat frameFormat);

    /// \brief      Call to open the CAN bus.
    /// \details    Creates a socket and binds it to the SocketCAN interface.
    /// \throws     LinuxCanBusException
    void Open();

private:

    std::string interfaceName_;

    /// \brief      Keeps track of whether the CAN interface has been started
    ///             via can_do_start().
    bool canInterfaceUp_;

    State state_;

    FrameFormat frameFormat_;

    int socketFd_;

    int bitRate_;

    struct ifreq ifr_;
    struct sockaddr_can addr_;

    std::mutex writeSysCallMutex_;

    static constexpr uint8_t CAN_ID_11_BIT_ADD_START_POS = 0;   ///< Bits [0:10]
    static constexpr uint8_t CAN_ID_18_BIT_ADD_START_POS = 11;  ///< Bits [11:28]
    static constexpr uint8_t CAN_ID_FRAME_FORMAT_BIT_POS = 31;  ///< Bits [31]


};