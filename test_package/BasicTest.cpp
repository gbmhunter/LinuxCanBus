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

    TEST_F(BasicTests, LinkedCorrectly) {
        LinuxApiReal linuxApiReal;
        LinuxCanBus linuxCanBus;
        linuxCanBus.Init(&linuxApiReal, "vcan0", 0, LinuxCanBus::FrameFormat::STANDARD);
        ASSERT_EQ(2, 2);
    }



}  // namespace