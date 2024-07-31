#include "gtest/gtest.h"

#include "logger.h"

class LoggerTest : public testing::Test {};

TEST_F (LoggerTest, simple_text_debug){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::debug << "simple text" << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[35m[D] simple text\x1B[0m\n");
}

TEST_F (LoggerTest, simple_text_info){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::info << "simple text" << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] simple text\x1B[0m\n");
}

TEST_F (LoggerTest, simple_text_warning){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::warning << "simple text" << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[33m[W] simple text\x1B[0m\n");
}

TEST_F (LoggerTest, simple_text_error){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::error << "simple text" << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[31m[E] simple text\x1B[0m\n");
}


TEST_F (LoggerTest, text_with_set_width){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::debug << logger::setw(50) << "simple text with width 50" << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[35m[D]                          simple text with width 50\x1B[0m\n");
}

TEST_F (LoggerTest, format_hex_with_set_width){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::debug << "12 hex with 10: " << logger::hex << logger::setw(10) << 12 << logger::dec << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[35m[D] 12 hex with 10: 0x000000000c\x1B[0m\n");
}

TEST_F (LoggerTest, format_hex_and_dec_after_that){
    uint32_t deadbeef = 0xDEADBEEF;

    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    logger::logger << logger::Logger::info << "print in hex: " << logger::hex << deadbeef << logger::dec << " print in dex:" << deadbeef << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print in hex: 0xdeadbeef print in dex:3735928559\x1B[0m\n");
}

TEST_F (LoggerTest, format_uint32_t_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    uint32_t AA = 0xDEADBEEF;
    logger::logger << logger::Logger::info << "print uint32_t:" << logger::hex << AA << " in bin: " << logger::bit(AA) << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint32_t:0xdeadbeef in bin: b11011110101011011011111011101111\x1B[0m\n");
}
TEST_F (LoggerTest, format_uint16_t_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    uint16_t BB = 0xBEEF;
    logger::logger << logger::Logger::info << "print uint16_t:" << logger::hex << BB << " in bin: " << logger::bit(BB) << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint16_t:0xbeef in bin: b1011111011101111\x1B[0m\n");
}
TEST_F (LoggerTest, format_uint64_t_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    uint64_t CC = 0xDEADBEEFDEADBEEF;
    logger::logger << logger::Logger::info << "print uint64_t:" << logger::hex << CC << " in bin: " << logger::bit(CC) << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint64_t:0xdeadbeefdeadbeef in bin: b1101111010101101101111101110111111011110101011011011111011101111\x1B[0m\n");
}
TEST_F (LoggerTest, format_UINT64_MAX_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    uint64_t DD = UINT64_MAX;
    logger::logger << logger::Logger::info << "print uint64_t:" << logger::hex << DD << " in bin: " << logger::bit(DD) << logger::Logger::end;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint64_t:0xffffffffffffffff in bin: b1111111111111111111111111111111111111111111111111111111111111111\x1B[0m\n");
}
