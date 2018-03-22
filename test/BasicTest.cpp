
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "LinuxCanBus/LinuxCanBus.hpp"

#include "MockLinuxApi.hpp"

using namespace testing;
using namespace mn::LinuxCanBus;

namespace {

    class BasicTests : public ::testing::Test {
    protected:

        BasicTests() {
        }

        virtual ~BasicTests() {
        }

        void Init() {
            linuxCanBus_.Init(&mockLinuxApi_, "vcan0", 0, LinuxCanBus::FrameFormat::STANDARD);
        }

        void Open() {
            // Socket should be opened to create end-point for CAN comms
            EXPECT_CALL(mockLinuxApi_, socket_(PF_CAN, SOCK_RAW, CAN_RAW))
                    .Times(1).WillRepeatedly(Return(fakeFileDescriptor));

            // Return 0 to indicate success
            EXPECT_CALL(mockLinuxApi_, ioctl_(fakeFileDescriptor, SIOCGIFINDEX, _))
                    .Times(1).WillRepeatedly(Return(0));

            EXPECT_CALL(mockLinuxApi_, fcntl_(fakeFileDescriptor, F_SETFL, O_NONBLOCK))
                    .Times(1).WillRepeatedly(Return(0));

            // Return 0 to indicate success
            EXPECT_CALL(mockLinuxApi_, bind_(fakeFileDescriptor, _, _))
                    .Times(1).WillRepeatedly(Return(0));


            linuxCanBus_.Open();
        }

        void Close() {
            // Return 0 to indicate success
            EXPECT_CALL(mockLinuxApi_, close_(fakeFileDescriptor))
                    .Times(1).WillRepeatedly(Return(0));

            linuxCanBus_.Close();
        }

        MockLinuxApi mockLinuxApi_;
        LinuxCanBus linuxCanBus_;
        const int fakeFileDescriptor = 12;

    };

    TEST_F(BasicTests, InitialStateCorrect) {
        LinuxCanBus linuxCanBus;
        EXPECT_EQ(linuxCanBus.GetState(), LinuxCanBus::State::CLOSED);
    }

    TEST_F(BasicTests, InitializedCorrectly) {
        Init();
        EXPECT_EQ(linuxCanBus_.GetInterfaceName(), "vcan0");
        EXPECT_EQ(linuxCanBus_.GetFrameFormat(), LinuxCanBus::FrameFormat::STANDARD);
    }

    TEST_F(BasicTests, OpenCorrectly) {
        Init();
        Open();
    }

    TEST_F(BasicTests, CloseCorrectly) {
        Init();
        Open();
        Close();
    }

}  // namespace