project(LinuxCanBusTest)
cmake_minimum_required(VERSION 2.8.12)
add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} BasicTest.cpp)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})

ENABLE_TESTING()
ADD_TEST(NAME Tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        COMMAND ${PROJECT_NAME})