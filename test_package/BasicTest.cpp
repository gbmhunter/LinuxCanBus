#include <gtest/gtest.h>

#include "LinuxCanBus/LinuxCanBus.hpp"

using namespace mn::LinuxCanBus;

namespace {

    class BasicTests : public ::testing::Test {
    protected:
        BasicTests() {}
        virtual ~BasicTests() {}
    };

    TEST_F(BasicTests, LinkedCorrectly) {        
        // The ability to create an object and call a function indicates that
        // the LinuxCanBus library was created and linked correctly
        LinuxCanBus linuxCanBus;
        linuxCanBus.Init("vcan0", LinuxCanBus::FrameFormat::STANDARD);        
    }



}  // namespace