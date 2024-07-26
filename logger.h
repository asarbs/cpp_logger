#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <ostream>
#include <iomanip>
#include <chrono>
#include <string>

#include "color.h"

namespace logger {

    struct _Setw {
            int _M_n;
    };

    inline _Setw setw(int __n) {
        return {__n};
    }

    struct _Sbit {
        const void* _object;
        size_t _size;
    };

    inline _Sbit bit(const void* object, size_t size) {
        return { object, size };
    }

    class Logger {
        public:
            enum LogLevel {
            DEBUG = 10,
            INFO = 20,
            WARNING = 30,
            ERROR = 40,
            CRITICAL = 50,
            };

            Logger(): __lastLogLevel(logger::Logger::LogLevel::DEBUG), __outWidth(0)  {
            }

            Logger& operator<<(bool value) {
                __msg << std::setw(__outWidth) << (value == true ? "t" : "f");
                __outWidth = 0;
                return *this;
            }
            Logger& operator<<(uint8_t value) {
                __msg << uint32_t(value);
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(long value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(unsigned long value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(unsigned int value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(long long value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(unsigned long long value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(double value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(long double value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(const void* value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(const volatile void* value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(short value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }
            Logger& operator<<(const signed int value) {
                // td::cout << "\r\n" << __FILE__ << ":" << __LINE__ << ":" << uint32_t(value) << "\"" << std::endl;
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }
            Logger& operator<<(const char* value) {
                // td::cout << "\r\n" << __FILE__ << ":" << __LINE__ << ":\"" << value << "\"" << std::endl;
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }
            Logger& operator<<(const unsigned char* value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(const std::string& value) {
                __msg << std::setw(__outWidth) << value;
                __outWidth = 0;
                return *this;
            }

            Logger& operator<<(_Setw __f) {
                // td::cout << "\r\n" << __FILE__ << ":" << __LINE__ << ":\"" << uint32_t(__f._M_n) << "\"" << std::endl;
                __outWidth = __f._M_n;
                return *this;
            }

            Logger& operator<<(_Sbit __f) {
                const uint32_t obj = *(static_cast<const uint32_t*>(__f._object));

                __msg << "b";
                for(uint32_t i = 0 ; i < __f._size ; i++) {
                     __msg << ( ( obj & (1 << i) ) == 0 );
                }

                __outWidth = 0;
                return *this;
            }

            // basic_ostream& operator<<( /* extended-floating-point-type */ value );
            // basic_ostream& operator<<(std::basic_streambuf<CharT, Traits>* sb );
            // basic_ostream& operator<<(std::ios_base& (*func)(std::ios_base&) );
            // basic_ostream& operator<<(std::basic_ios<CharT, Traits>& (*func)(std::basic_ios<CharT, Traits>&) );
            // basic_ostream& operator<<(std::basic_ostream<CharT, Traits>& (*func)(std::basic_ostream<CharT, Traits>&) );

            Logger& operator<<(Logger& (*__p_fun)(Logger&)) {
                return __p_fun(*this);
            }

            static Logger& end(Logger& l) {
                if(l.__lastLogLevel >= Logger::__currentLogLevel) {
                    auto now = std::chrono::system_clock::now();
                    auto in_time_t = std::chrono::system_clock::to_time_t(now);
                    auto ms = duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
                    std::cout << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S") << "." << std::setfill('0') << std::setw(6) << ms.count() << l.__msg.str() << Color::reset << std::endl;
                }
                l.__msg.str("");
                l.__outWidth = 0;
                l.__msg.fill(' ');
                l.__msg.width(0);
                return l;
            }

            static Logger& debug(Logger& l){
                l.__lastLogLevel = LogLevel::DEBUG;
                l.__msg  << Color::magenta << "[D] ";
                
                return l;
            }
            static Logger& info(Logger& l){
                l.__lastLogLevel = LogLevel::INFO;
                l.__msg << Color::green << "[I] ";
                
                return l;
            }
            static Logger& warning(Logger& l){
                l.__lastLogLevel = LogLevel::WARNING;
                l.__msg << Color::yellow << "[W] ";
                return l;
            }
            static Logger& error(Logger& l){
                l.__lastLogLevel = LogLevel::ERROR;
                l.__msg << Color::red << "[E] ";
                
                return l;
            }
            static Logger& critical(Logger& l){
                l.__lastLogLevel = LogLevel::CRITICAL;
                l.__msg << Color::bg_red << "[C] ";
                
                return l;
            }

            static void setLogLevel(LogLevel newLogLevel) {
                __currentLogLevel = newLogLevel;
            }
            friend Logger& hex(Logger& l);
            friend Logger& dec(Logger& l);

        protected:

        private:
            std::stringstream __msg;
            inline static LogLevel   __currentLogLevel = LogLevel::DEBUG;
            LogLevel          __lastLogLevel;
            uint8_t           __outWidth;
    };

    inline static Logger logger;

    inline Logger& hex(Logger& l){
        l.__msg << "0x" << std::setfill('0') << std::hex;
        return l;
    }

    inline Logger& dec(Logger& l) {
        l.__msg  << std::dec;
        return l;
    }
};

#endif // LOGGER

