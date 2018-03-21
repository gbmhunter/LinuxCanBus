#!/usr/bin/env bash

# The all-in-one command
# Install all dependencies, build project, create package
# and run tests
conan create . mbeddedninja/testing

exit 0

# Install conan dependencies
conan install .

# Create build dir and run build
mkdir -p build
cd build
conan build ..