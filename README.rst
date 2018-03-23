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

