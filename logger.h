#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <ostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <bitset>

#include "color.h"

namespace logger {

    struct _Setw {
            int _M_n;
    };

    inline _Setw setw(int __n) {
        return {__n};
    }

    template<typename T>
    struct _Sbit {
        T _object;
    };

    template<typename T>
    inline _Sbit<T> bit(T object) {
        return { object };
    }

    class LogLevel2;

    class Logger {
        public:

            class LogLevel {
                public:
                    LogLevel(uint32_t level, Color::Modifier color, const char* sign): __level(level), __color(color), __sign(0) {
                        memcpy(static_cast<void*>(&__sign), static_cast<const void*>(sign), sizeof(char));
                    };

                    Logger& operator<<(Logger& in) {
                        return in;
                    }

                    uint32_t __level;
                    char __sign; 
                    Color::Modifier __color;
                protected:
                private:
                    LogLevel();
                    LogLevel(LogLevel& o);
                    LogLevel operator=(LogLevel o);

            };

            Logger(): __lastLogLevel(0), __outWidth(0)  {
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

            template<typename T>
            Logger& operator<<(_Sbit<T> __f) {
                std::bitset<sizeof(T)*8> b_obj(__f._object);
                __msg << "b" << b_obj.to_string();
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
                if(l.__lastLogLevel >= l.__currentLogLevel) {
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

            Logger& operator<<(const LogLevel& in) {

                this->__lastLogLevel = in.__level;
                this->__msg << in.__color << "[" << in.__sign << "] ";

                return *this;
            }   

            void setLogLevel(const LogLevel& in) {
                __currentLogLevel = in.__level;
            }
            friend Logger& hex(Logger& l);
            friend Logger& dec(Logger& l);

        protected:

        private:
            std::stringstream __msg;
            uint32_t __currentLogLevel = 0;
            uint32_t          __lastLogLevel;
            uint8_t           __outWidth;
    };

    inline static Logger logger;

    inline static logger::Logger::LogLevel debug(10, Color::magenta, "D"); 
    inline static logger::Logger::LogLevel info(20, Color::green, "I"); 
    inline static logger::Logger::LogLevel warning(30, Color::yellow, "W"); 
    inline static logger::Logger::LogLevel error(40, Color::red, "E"); 
    inline static logger::Logger::LogLevel critical(50, Color::bg_red, "C"); 

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

