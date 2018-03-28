Basic Example
=============

.. code-block:: cpp

    #include "LinuxCanBus/LinuxCanBus.hpp"

    int main() {

        LinuxCanBus canBus;

        // Setup CAN bus using interface can0, 250000 baud, and standard frame format (i.e. not extended)
        canBus.Init("can0", 250000, LinuxCanBus::FrameFormat::STANDARD);

        // Write to CAN bus
        CanMsg writeMsg;
        writeMsg.SetAddress(0x01);
        writeMsg.GetDataMutable().push_back(0x12);
        writeMsg.GetDataMutable().push_back(0x34);
        canBus.Write(writeMsg);

        // Read from CAN bus
        CanMsg readMsg;
        canBus.Read(readMsg, 0);

        return 0;
    }