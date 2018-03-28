Installation
============

----------------------------
Automatic Build/Test/Package
----------------------------

Requires Conan to be installed.

.. code:: bash

    ~/LinuxCanBus$ conan create . testuser/testing

This will provide a static library called libLinuxCanBus.a and header files under a folder called :code:`include/LinuxCanBus`, available to other Conan packages.

------------
Manual Build
------------

.. code:: bash

    ~/LinuxCanBus$ mkdir build
    ~/LinuxCanBus$ cd build/
    ~/LinuxCanBus/build$ conan install ..
    ~/LinuxCanBus/build$ conan build ..

This will build a static library called libLinuxCanBus.a and header files under a folder called :code:`include/LinuxCanBus`.

Once you have installed LinuxCanBus, go to the :doc:`Basic Example page </usage/basic_example>` to see how to use it!

-------------
Documentation
-------------

This documentation was created with `sphinx <http://www.sphinx-doc.org>`_. To build the documentation, first make sure `sphinx is installed <https://docs.readthedocs.io/en/latest/getting_started.html#in-restructuredtext>`_, and then navigate to the docs/ folder and run:

.. code:: bash

    make html