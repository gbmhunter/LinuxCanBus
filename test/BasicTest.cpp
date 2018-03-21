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

    };

    TEST_F(BasicTests, InitializedCorrectly) {

        LinuxApiReal linuxApiReal;

        LinuxCanBus linuxCanBus;
        linuxCanBus.Init(&linuxApiReal, "vcan0", 0, LinuxCanBus::FrameFormat::STANDARD);
        EXPECT_EQ(linuxCanBus.GetInterfaceName(), "vcan0");
        EXPECT_EQ(linuxCanBus.GetFrameFormat(), LinuxCanBus::FrameFormat::STANDARD);
    }

}  // namespace