#include <gtest/gtest.h>

#include "LinuxCanBus/LinuxCanBus.hpp"

using namespace mn::LinuxCanBus;

namespace {

    class BasicTests : public ::testing::Test {
    protected:

        BasicTests() {
        }

        virtual ~BasicTests() {
        }

        LinuxApiReal linuxApiReal_;

    };

    TEST_F(BasicTests, InitialStateCorrect) {
        LinuxCanBus linuxCanBus;
        EXPECT_EQ(linuxCanBus.GetState(), LinuxCanBus::State::CLOSED);
    }

    TEST_F(BasicTests, InitializedCorrectly) {
        LinuxCanBus linuxCanBus;
        linuxCanBus.Init(&linuxApiReal_, "vcan0", 0, LinuxCanBus::FrameFormat::STANDARD);
        EXPECT_EQ(linuxCanBus.GetInterfaceName(), "vcan0");
        EXPECT_EQ(linuxCanBus.GetFrameFormat(), LinuxCanBus::FrameFormat::STANDARD);
    }

}  // namespace