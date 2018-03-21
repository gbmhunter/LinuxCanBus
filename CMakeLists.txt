project(LinuxCanBusCpp)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(Demo src/LinuxCanBusCpp.cpp)
target_link_libraries(Demo ${CONAN_LIBS})