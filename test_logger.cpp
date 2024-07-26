#include "gtest/gtest.h"

#include "logger.h"

class LoggerTest : public testing::Test {};


TEST_F (LoggerTest, example){
    testing::internal::CaptureStdout();


    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    bool b = false;
    bool x = true;

    uint32_t AA = 0xDEADBEEF;
    uint16_t BB = 0xDEAD;
    uint64_t CC = 0xDEADBEEFDEADBEEF;
    uint64_t DD = UINT64_MAX;
    uint32_t deadbeef = 0xDEADBEEF;

    logger::logger << logger::Logger::debug << "simple text" << logger::Logger::end;
    logger::logger << logger::Logger::debug << logger::setw(50) << "simple text with width 50" << logger::Logger::end;
    logger::logger << logger::Logger::debug << "12 hex with 10: " << logger::hex << logger::setw(10) << 12 << logger::dec << logger::Logger::end;
    logger::logger << logger::Logger::debug << 12 << " " << " AAA " << logger::hex << 12 << logger::dec << logger::Logger::end;
    logger::logger << logger::Logger::info << 12 << 15 << " " << 12.4 << " " << __LONG_LONG_MAX__ << logger::Logger::end;
    logger::logger << logger::Logger::info << "print in hex: " << logger::hex << deadbeef << logger::dec << " print in dex:" << deadbeef << logger::Logger::end;
    logger::logger << logger::Logger::info << "print uint32_t:" << logger::hex << AA << " in bin: " << logger::bit(AA) << logger::Logger::end;
    logger::logger << logger::Logger::info << "print uint16_t:" << logger::hex << BB << " in bin: " << logger::bit(BB) << logger::Logger::end;
    logger::logger << logger::Logger::info << "print uint64_t:" << logger::hex << CC << " in bin: " << logger::bit(CC) << logger::Logger::end;
    logger::logger << logger::Logger::info << "print uint64_t:" << logger::hex << DD << " in bin: " << logger::bit(DD) << logger::Logger::end;
    logger::logger << logger::Logger::info << "print hex with leading 0: " << logger::hex << logger::setw(8) << 0xDE << logger::dec<< logger::Logger::end;
    logger::logger << logger::Logger::warning << 12 << 15 << logger::Logger::end;
    logger::logger << logger::Logger::error << 12 << 15 << logger::Logger::end;
    logger::logger << logger::Logger::critical << 12 << " " << 15 << " " << b << " A " << x << logger::Logger::end;

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "My test");
}
