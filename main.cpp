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



int main() {

    logger::logger.setLogLevel(logger::Logger::LogLevel::DEBUG);
    bool b = false;
    bool x = true;

    uint32_t AA = 0xAAAAAAAA;
    uint32_t deadbeef = 0xDEADBEEF;

    logger::logger << logger::Logger::debug << "simple text" << logger::Logger::end;
    logger::logger << logger::Logger::debug << logger::setw(50) << "simple text with width 50" << logger::Logger::end;
    logger::logger << logger::Logger::debug << "12 hex with 10: " << logger::hex << logger::setw(10) << 12 << logger::dec << logger::Logger::end;
    logger::logger << logger::Logger::debug << 12 << " " << " AAA " << logger::hex << 12 << logger::dec << logger::Logger::end;
    logger::logger << logger::Logger::info << 12 << 15 << " " << 12.4 << " " << __LONG_LONG_MAX__ << logger::Logger::end;
    logger::logger << logger::Logger::info << "print in hex: " << logger::hex << deadbeef << logger::dec << " print in dex:" << deadbeef << logger::Logger::end;
    logger::logger << logger::Logger::info << "print " << logger::hex << AA << " in bin: " << logger::bit(static_cast<void*>(&AA), 32) << logger::Logger::end;
    logger::logger << logger::Logger::info << "print hex with leading 0: " << logger::hex << logger::setw(8) << 0xDE << logger::dec<< logger::Logger::end;
    logger::logger << logger::Logger::warning << 12 << 15 << logger::Logger::end;
    logger::logger << logger::Logger::error << 12 << 15 << logger::Logger::end;
    logger::logger << logger::Logger::critical << 12 << " " << 15 << " " << b << " A " << x << logger::Logger::end;

    
    return 0;
}

