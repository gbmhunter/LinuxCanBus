#include <gtest/gtest.h>

#include "LinuxCanBus/LinuxCanBus.hpp"

using namespace mn::LinuxCanBus;

TEST(TestingEncryption, cipher) {

    LinuxCanBus linuxCanBus;
    linuxCanBus.Init("vcan0", 0, LinuxCanBus::FrameFormat::STANDARD);
    ASSERT_EQ(2, 2);

}