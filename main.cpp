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
    logger::logger << logger::Logger::debug << "simple text" << logger::Logger::end;
    logger::logger << logger::Logger::debug << 12 << " " << " AAA " << logger::Logger::hex << logger::Logger::end;
    logger::logger << logger::Logger::info << 12 << 15 << " " << 12.4 << " " << __LONG_LONG_MAX__ << logger::Logger::end;
    logger::logger << logger::Logger::info << logger::Logger::hex << 0xDEADBEEF << logger::Logger::end;
    logger::logger << logger::Logger::info << logger::Logger::hex << logger::setw(8) << 0xDE << logger::Logger::end;
    logger::logger << logger::Logger::warning << 12 << 15 << logger::Logger::end;
    logger::logger << logger::Logger::error << 12 << 15 << logger::Logger::end;
    logger::logger << logger::Logger::critical << 12 << " " << 15 << " " << b << " A " << x << logger::Logger::end;

    
    return 0;
}

