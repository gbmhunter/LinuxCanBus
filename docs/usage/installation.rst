Installation
============

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