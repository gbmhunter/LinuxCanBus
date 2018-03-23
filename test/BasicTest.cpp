
// Linux includes
#include <linux/can.h>

// 3rd party includes
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <LinuxCanBus/CanMsg.hpp>

// Local includes
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

        void Write(const CanMsg& msg, can_frame& canFrame) {

            EXPECT_CALL(mockLinuxApi_, write_(fakeFileDescriptor, _, _)).Times(1).WillRepeatedly(testing::Invoke(
                    [&] (int fd, const void *buf, size_t count) -> ssize_t {

                        // Cast pointer to can_frame pointer and then copy to provided canFrame object
                        canFrame = *(can_frame*)(buf);

                        // Return the number of bytes written, indicating success
                        return count;
                    }
            ));

            linuxCanBus_.Write(msg);
        }

        void Read(const can_frame& canFrame, CanMsg& msg) {

            // Returning 1 indicates there is data to be read
            EXPECT_CALL(mockLinuxApi_, select_(_, _, _, _, _)).Times(1).WillRepeatedly(Return(1));


            EXPECT_CALL(mockLinuxApi_, read_(fakeFileDescriptor, _, _)).Times(1).WillRepeatedly(testing::Invoke(
                    [&] (int fd, const void *buf, size_t count) -> ssize_t {

                        // Cast pointer to can_frame pointer and then copy from provided canFrame object
                        *(can_frame*)(buf) = canFrame;

                        // Return the number of bytes written, indicating success
                        return count;
                    }
            ));

            // Don't need to specify a non-zero timeout as mock API will provide data
            // immediately
            linuxCanBus_.Read(msg, 0);
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
        EXPECT_EQ(linuxCanBus_.GetState(), LinuxCanBus::State::OPEN);
    }

    TEST_F(BasicTests, CloseCorrectly) {
        Init();
        Open();
        Close();
        EXPECT_EQ(linuxCanBus_.GetState(), LinuxCanBus::State::CLOSED);
    }

    TEST_F(BasicTests, Write) {
        Init();
        Open();

        CanMsg msg;
        msg.SetAddress(0x1);
        msg.GetDataMutable().push_back(0x12);
        msg.GetDataMutable().push_back(0x34);

        can_frame canFrame;
        Write(msg, canFrame);

        EXPECT_EQ(canFrame.can_id, 0x1);

        // We provided 2 bytes of data (0x12, 0x34)
        EXPECT_EQ(canFrame.can_dlc, 2);
        EXPECT_EQ(canFrame.data[0], 0x12);
        EXPECT_EQ(canFrame.data[1], 0x34);
    }

    TEST_F(BasicTests, Read) {
        Init();
        Open();

        can_frame canFrame;
        canFrame.can_id = 0x1;
        canFrame.can_dlc = 3;
        canFrame.data[0] = 0x66;
        canFrame.data[1] = 0x77;
        canFrame.data[2] = 0x88;

        CanMsg msg;

        Read(canFrame, msg);

        EXPECT_EQ(msg.GetAddress(), 0x1);

        // We provided 3 bytes of data (0x66, 0x77, 0x88)
        EXPECT_EQ(msg.GetData().size(), 3);
        EXPECT_EQ(msg.GetData()[0], 0x66);
        EXPECT_EQ(msg.GetData()[1], 0x77);
        EXPECT_EQ(msg.GetData()[2], 0x88);
    }

}  // namespace