project(LinuxCanBus)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB_RECURSE LinuxCanBus_SRC "src/*.cpp")
file(GLOB_RECURSE LinuxCanBus_HDR "include/*.hpp")

add_library(LinuxCanBus ${LinuxCanBus_SRC} ${LinuxCanBus_HDR})
target_link_libraries(LinuxCanBus ${CONAN_LIBS})
target_include_directories(LinuxCanBus PUBLIC include/)

add_subdirectory(test/)