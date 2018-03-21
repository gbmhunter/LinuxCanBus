===========
CppTemplate
===========

-----------------------------------------------------------------------------------------
A template repository to quick-start C++ development.
-----------------------------------------------------------------------------------------

.. image:: https://travis-ci.org/mbedded-ninja/CppTemplate.svg?branch=master
	:target: https://travis-ci.org/mbedded-ninja/CppTemplate

.. image:: https://codecov.io/gh/mbedded-ninja/CppTemplate/branch/master/graph/badge.svg
    :target: https://codecov.io/gh/mbedded-ninja/CppTemplate

--------
Features
--------

- C++14 template/example project with example header files and source files
- CMake-based build system
- Automatic build script in ./tools/
- gtest-based unit tests (and a make target to automatically build/run unit tests)
- CI functionality using TravisCI (with sudo available on Ubuntu 14.04)
- Semantic versioning and keepachangelog.com-based Changelog format
- Doyxgen support (example :code:`doxygen.conf` file provided) coupled with GitHub pages support, see https://mbedded-ninja.github.io/CppTemplate/index.html for example documentation.
- Code coverage support using lcov and https://codecov.io. Code coverage is only generated for the files which matter, the source code in :code:`src/` and :code:`include/` directories.

---------------
Automatic Build
---------------

.. code:: bash

    ~/CppTemplate$ ./tools/build.sh

------------
Manual Build
------------

.. code:: bash

    ~/CppTemplate$ mkdir build
    ~/CppTemplate$ cd build/
    ~/CppTemplate/build$ cmake ..
    ~/CppTemplate/build$ make
    ~/CppTemplate/build$ make run_unit_tests
    ~/CppTemplate/build$ sudo make install

-------------------------
To Generate Documentation
-------------------------

.. code:: bash

    ~/CppTemplate$ doxygen doxygen.conf