Installation
============

----------------------------
Automatic Build/Test/Package
----------------------------

Requires Conan to be installed.

.. code:: bash

    ~/LinuxCanBus$ conan create . testuser/testing

This will provide a static library called libLinuxCanBus.a and header files under a folder called :code:`:LinuxCanBus`, available to other Conan packages.

------------
Manual Build
------------

.. code:: bash

    ~/LinuxCanBus$ mkdir build
    ~/LinuxCanBus$ cd build/
    ~/LinuxCanBus/build$ conan install ..
    ~/LinuxCanBus/build$ conan build ..

This will build a static library called libLinuxCanBus.a and header files under a folder called :code:`:LinuxCanBus`.