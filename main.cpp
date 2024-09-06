#include <iostream>
#include <bitset>
#include <memory>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <iomanip>
#include <mutex>
#include <typeinfo>


#include "logger.h"

static std::mutex mutex;

#define D2US   86400000000
#define H2US   3600000000
#define M2US   60000000
#define S2US   1000000
#define MS2US  1000

std::string logger_format_time_str(uint64_t time_us) {
    struct time_stamp {
    uint32_t days;
    uint32_t hour;
    uint32_t minute;
    uint32_t second;
    uint32_t millisecond;
    uint32_t microsecond;
};

    static struct time_stamp ts;
    static uint64_t          days_left, hour_left, minute_left, second_left, millisecond_left;

    ts.days   = time_us / D2US;
    days_left = time_us - (ts.days * D2US);

    ts.hour   = days_left / H2US;
    hour_left = days_left - (ts.hour * H2US);

    ts.minute   = hour_left / M2US;
    minute_left = hour_left - (ts.minute * M2US);

    ts.second   = minute_left / S2US;
    second_left = minute_left - (ts.second * S2US);

    ts.millisecond   = second_left / MS2US;
    millisecond_left = second_left - (ts.millisecond * MS2US);

    ts.microsecond = millisecond_left % MS2US;

    std::stringstream ss;

    ss  << std::setfill('0') << std::setw(2) << ts.days << " "  //
        << std::setfill('0') << std::setw(2) << ts.hour << ":" //
        << std::setfill('0') << std::setw(2) << ts.minute << ":" //
        << std::setfill('0') << std::setw(2) << ts.second <<"." //
        << std::setfill('0') << std::setw(3) << ts.millisecond << "." //
        << std::setfill('0') << std::setw(3) << ts.microsecond;
    return ss.str();
}


int main() {
    logger::logger.setLogLevel(logger::debug);
    bool b = false;
    bool x = true;

    uint32_t AA = 0xDEADBEEF;
    uint16_t BB = 0xDEAD;
    uint64_t CC = 0xDEADBEEFDEADBEEF;
    uint64_t DD = UINT64_MAX;
    uint32_t deadbeef = 0xDEADBEEF;
    
    logger::logger << logger::debug << "simple text" << logger::Logger::end;
    logger::logger << logger::debug << logger::setw(50) << "simple text with width 50" << logger::Logger::end;
    logger::logger << logger::debug << "12 hex with 10: " << logger::hex << logger::setw(10) << 12 << logger::dec << logger::Logger::end;
    logger::logger << logger::debug << 12 << " " << " AAA " << logger::hex << 12 << logger::dec << logger::Logger::end;
    logger::logger << logger::info << 12 << 15 << " " << 12.4 << " " << __LONG_LONG_MAX__ << logger::Logger::end;
    logger::logger << logger::info << "print in hex: " << logger::hex << deadbeef << logger::dec << " print in dex:" << deadbeef << logger::Logger::end;
    logger::logger << logger::info << "print uint32_t:" << logger::hex << AA << " in bin: " << logger::bit(AA) << logger::Logger::end;
    logger::logger << logger::info << "print uint16_t:" << logger::hex << BB << " in bin: " << logger::bit(BB) << logger::Logger::end;
    logger::logger << logger::info << "print uint64_t:" << logger::hex << CC << " in bin: " << logger::bit(CC) << logger::Logger::end;
    logger::logger << logger::info << "print uint64_t:" << logger::hex << DD << " in bin: " << logger::bit(DD) << logger::Logger::end;
    logger::logger << logger::info << "print hex with leading 0: " << logger::hex << logger::setw(8) << 0xDE << logger::dec<< logger::Logger::end;
    logger::logger << logger::warning << 12 << 15 << logger::Logger::end;
    logger::logger << logger::error << 12 << 15 << logger::Logger::end;
    logger::logger << logger::critical << 12 << " " << 15 << " " << b << " A " << x << logger::Logger::end;

    logger::Logger::LogLevel new_log_level(60, Color::BG_BLUE, "A");
    logger::logger.setLogLevel(new_log_level);
    logger::logger << new_log_level << "Test Str" << logger::Logger::end;

    logger::Logger::LogLevel new_log_level2(60, Color::BG_GREEN, "B");


    return 0;
}

