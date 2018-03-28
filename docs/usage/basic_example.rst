Basic Example
=============

NOTE: LinuxCanBus does not configure and bring "up" the CAN interface itself. This has to be done with command-lind calls to :code:`ip link` and similar before using the library.

.. code-block:: cpp

    #include "LinuxCanBus/LinuxCanBus.hpp"

    int main() {

        LinuxCanBus canBus;

        // Setup CAN bus using CAN interface can0 and the standard frame format (i.e. not extended)
        canBus.Init("can0", LinuxCanBus::FrameFormat::STANDARD);

        // Write to CAN bus
        CanMsg writeMsg;
        writeMsg.SetAddress(0x01);
        writeMsg.GetDataMutable().push_back(0x12);
        writeMsg.GetDataMutable().push_back(0x34);
        canBus.Write(writeMsg);

        // Read from CAN bus, if available
        // (0 means no blocking)
        CanMsg readMsg;
        canBus.Read(readMsg, 0);

        return 0;
    }