project(LinuxCanBus)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(LinuxCanBus src/LinuxCanBus.cpp include/LinuxCanBus/LinuxCanBus.hpp)
target_link_libraries(LinuxCanBus ${CONAN_LIBS})
target_include_directories(LinuxCanBus PUBLIC include/)

add_subdirectory(test/)