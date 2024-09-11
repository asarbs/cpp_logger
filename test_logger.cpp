#include "gtest/gtest.h"

#include <stdexcept>
#include <exception>

#include "logger.h"

class LoggerTest : public testing::Test {};

TEST_F (LoggerTest, simple_text_debug){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::debug << "simple text" << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[35m[D] simple text\x1B[0m\n");
}

TEST_F (LoggerTest, simple_text_info){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::info << "simple text" << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] simple text\x1B[0m\n");
}

TEST_F (LoggerTest, simple_text_warning){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::warning << "simple text" << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[33m[W] simple text\x1B[0m\n");
}

TEST_F (LoggerTest, simple_text_error){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::error << "simple text" << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[31m[E] simple text\x1B[0m\n");
}


TEST_F (LoggerTest, text_with_set_width){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::debug << logger::setw(50) << "simple text with width 50" << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[35m[D]                          simple text with width 50\x1B[0m\n");
}

TEST_F (LoggerTest, format_hex_with_set_width){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::debug << "12 hex with 10: " << logger::hex << logger::setw(10) << 12 << logger::dec << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[35m[D] 12 hex with 10: 0x000000000c\x1B[0m\n");
}

TEST_F (LoggerTest, format_hex_and_dec_after_that){
    uint32_t deadbeef = 0xDEADBEEF;

    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    logger::logger << logger::info << "print in hex: " << logger::hex << deadbeef << logger::dec << " print in dex:" << deadbeef << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print in hex: 0xdeadbeef print in dex:3735928559\x1B[0m\n");
}

TEST_F (LoggerTest, format_uint32_t_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    uint32_t AA = 0xDEADBEEF;
    logger::logger << logger::info << "print uint32_t:" << logger::hex << AA << " in bin: " << logger::bit(AA) << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint32_t:0xdeadbeef in bin: b11011110101011011011111011101111\x1B[0m\n");
}
TEST_F (LoggerTest, format_uint16_t_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    uint16_t BB = 0xBEEF;
    logger::logger << logger::info << "print uint16_t:" << logger::hex << BB << " in bin: " << logger::bit(BB) << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint16_t:0xbeef in bin: b1011111011101111\x1B[0m\n");
}
TEST_F (LoggerTest, format_uint64_t_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    uint64_t CC = 0xDEADBEEFDEADBEEF;
    logger::logger << logger::info << "print uint64_t:" << logger::hex << CC << " in bin: " << logger::bit(CC) << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint64_t:0xdeadbeefdeadbeef in bin: b1101111010101101101111101110111111011110101011011011111011101111\x1B[0m\n");
}
TEST_F (LoggerTest, format_UINT64_MAX_hex_and_bin){
    testing::internal::CaptureStdout();
    logger::logger.setLogLevel(logger::debug);
    uint64_t DD = UINT64_MAX;
    logger::logger << logger::info << "print uint64_t:" << logger::hex << DD << " in bin: " << logger::bit(DD) << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[32m[I] print uint64_t:0xffffffffffffffff in bin: b1111111111111111111111111111111111111111111111111111111111111111\x1B[0m\n");
}

TEST_F(LoggerTest, create_new_log_level) {
    testing::internal::CaptureStdout();

    logger::Logger::LogLevel new_log_level(60, Color::BG_BLUE, "A");

    logger::logger.setLogLevel(new_log_level);
    logger::logger << new_log_level << "Test Str" << logger::endl;
    std::string output = testing::internal::GetCapturedStdout().substr(26);

    EXPECT_EQ(output, "\x1B[44m[A] Test Str\x1B[0m\n");    
}

TEST_F(LoggerTest, create_new_log_levels_with_the_same_level_number) {
    logger::Logger::LogLevel new_log_level1(70, Color::BG_BLUE, "A");

    EXPECT_THROW(logger::Logger::LogLevel new_log_level2(70, Color::BG_GREEN, "B"), std::logic_error);

}
