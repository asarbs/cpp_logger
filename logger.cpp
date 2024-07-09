#include "logger.h"


std::vector<uint32_t> logger::Logger::LogLevel::__level_collection = std::vector<uint32_t>();

logger::Logger::LogLevel::LogLevel(uint32_t level, Color::Modifier color, const char* sign): __level(level), __sign(0), __color(color) {
    memcpy(static_cast<void*>(&__sign), static_cast<const void*>(sign), sizeof(char));
    auto it = std::find(__level_collection.begin(), __level_collection.end(), __level);
    if(it == __level_collection.end()) {
        // std::cout << Color::green << "Created:" << __level  << Color::reset<< std::endl;
        __level_collection.push_back(__level);
    } else {
        throw std::logic_error("LogLevel already used.");
    }
};

logger::Logger& logger::Logger::LogLevel::operator<<(logger::Logger& in) {
    return in;
}

uint32_t logger::Logger::LogLevel::get_level() const {
    return __level;
}
char logger::Logger::LogLevel::get_sign() const {
    return __sign;
}
Color::Modifier logger::Logger::LogLevel::get_color() const {
    return __color;
}

logger::Logger::LogLevel logger::debug      = {10, Color::magenta,  "D"}; 
logger::Logger::LogLevel logger::info       = {20, Color::green,    "I"}; 
logger::Logger::LogLevel logger::warning    = {30, Color::yellow,   "W"}; 
logger::Logger::LogLevel logger::error      = {40, Color::red,      "E"}; 
logger::Logger::LogLevel logger::critical   = {50, Color::bg_red,   "C"}; 

logger::Logger& logger::Logger::getInstance() {
    static logger::Logger inst;
    return inst;
}

logger::Logger& logger::logger = logger::Logger::getInstance();

logger::Logger::Logger(): __lastLogLevel(0), __outWidth(0)  {

}

logger::Logger& logger::Logger::operator<<(bool value) {
    __msg << std::setw(__outWidth) << (value == true ? "t" : "f");
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(uint8_t value) {
    __msg << uint32_t(value);
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(long value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(unsigned long value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(unsigned int value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(long long value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(unsigned long long value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(double value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(long double value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const void* value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const volatile void* value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(short value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const signed int value) {
    // td::cout << "\r\n" << __FILE__ << ":" << __LINE__ << ":" << uint32_t(value) << "\"" << std::endl;
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const char* value) {
    // td::cout << "\r\n" << __FILE__ << ":" << __LINE__ << ":\"" << value << "\"" << std::endl;
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const unsigned char* value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const std::string& value) {
    __msg << std::setw(__outWidth) << value;
    __outWidth = 0;
    return *this;
}
logger::Logger& logger::Logger::operator<<(logger::Logger& (*__p_fun)(logger::Logger&)) {
    return __p_fun(*this);
}
logger::Logger&  logger::Logger::operator<<(logger::_Setw __f) {
    // td::cout << "\r\n" << __FILE__ << ":" << __LINE__ << ":\"" << uint32_t(__f._M_n) << "\"" << std::endl;
    __outWidth = __f._M_n;
    return *this;
}
logger::Logger& logger::Logger::operator<<(const logger::Logger::LogLevel& in) {
    this->__lastLogLevel = in.get_level();
    this->__msg << in.get_color() << "[" << in.get_sign() << "] ";

    return *this;
}

logger::Logger&  logger::Logger::__flush() {
    if(__lastLogLevel >= __currentLogLevel) {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
        std::cout << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S") << "." << std::setfill('0') << std::setw(6) << ms.count() << __msg.str() << Color::reset << std::endl;
    }
    __msg.str("");
    __outWidth = 0;
    __msg.fill(' ');
    __msg.width(0);
    return *this;
}

void logger::Logger::setLogLevel(const logger::Logger::LogLevel& in) {
    __currentLogLevel = in.get_level();
}

logger::Logger& logger::hex(logger::Logger& l){
    l.__msg << "0x" << std::setfill('0') << std::hex;
    return l;
}

logger::Logger& logger::dec(logger::Logger& l) {
    l.__msg  << std::dec;
    return l;
}

logger::Logger& logger::endl(logger::Logger& l) {
    return l.__flush();
}
