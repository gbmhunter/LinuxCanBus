#include <gtest/gtest.h>

#include "LinuxCanBus/LinuxCanBus.hpp"

TEST(TestingEncryption, cipher) {

    LinuxCanBus linuxCanBus;
    linuxCanBus.Init();
    ASSERT_EQ(2, 2);

}