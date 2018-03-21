

add_executable(UnitTests BasicTest.cpp)
target_link_libraries(UnitTests ${CONAN_LIBS} LinuxCanBus)
target_include_directories(UnitTests PUBLIC ../include/)
