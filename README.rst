===========
LinuxCanBus
===========

-----------------------------------------------------------------------------------------
A C++ user-space CAN bus driver for Linux (using socketCAN).
-----------------------------------------------------------------------------------------

.. image:: https://travis-ci.org/mbedded-ninja/CppTemplate.svg?branch=master
	:target: https://travis-ci.org/mbedded-ninja/CppTemplate

.. image:: https://codecov.io/gh/mbedded-ninja/CppTemplate/branch/master/graph/badge.svg
    :target: https://codecov.io/gh/mbedded-ninja/CppTemplate

--------
Features
--------

- Easy to use API for controller a CAN device in Linux
- CMake-based build system
- Conan (package manager) support

-------
Example
-------

.. code:: cpp
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

----------------------------
Automatic Build/Test/Package
----------------------------

Requires Conan to be installed.

.. code:: bash

    ~/LinuxCanBus$ conan create . testuser/testing

------------
Manual Build
------------

.. code:: bash

    ~/LinuxCanBus$ mkdir build
    ~/LinuxCanBus$ cd build/
    ~/LinuxCanBus/build$ conan install ..
    ~/LinuxCanBus/build$ conan build ..

