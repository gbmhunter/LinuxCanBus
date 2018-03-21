#include <gtest/gtest.h>

#include "LinuxCanBus/LinuxCanBus.hpp"

TEST(TestingEncryption, cipher) {

    LinuxCanBus linuxCanBus;
    linuxCanBus.Init("vcan0", 0, LinuxCanBus::FrameFormat::STANDARD);
    ASSERT_EQ(2, 2);

}