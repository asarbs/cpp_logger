#include "logger.h"

#include <chrono>

#include "color.h"
#include <iostream>

logger::Logger::LogLevel logger::Logger::__currentLogLevel = logger::Logger::LogLevel::DEBUG;

logger::Logger::Logger() : __lastLogLevel(logger::Logger::LogLevel::DEBUG), __outWidth(0) {
}

logger::Logger& logger::Logger::end(logger::Logger& l) {
    if(l.__lastLogLevel >= Logger::__currentLogLevel) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
        std::cout << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S") << "." << std::setfill('0') << std::setw(6) << ms.count() << l.__msg.str() << Color::reset << std::endl;
    }
    l.__msg.str("");
    l.__outWidth = 0;
    return l;
}

logger::Logger& logger::Logger::hex(logger::Logger& l) {
    l.__msg << "0x" << std::setfill('0') << std::hex;
    return l;
}

void logger::Logger::setLogLevel(logger::Logger::LogLevel newLogLevel) {
    Logger::__currentLogLevel = newLogLevel;
}
