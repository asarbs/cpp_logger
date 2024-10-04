#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <ostream>
#include <iomanip>
#include <chrono>
#include <string>
#include <bitset>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <exception>

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

    template<typename T>
    struct _SArray {
        const T* _object;
        size_t _size;
    };

    template<typename T>
    inline _SArray<T> array(const T* object, size_t size) {
        return {object, size};
    }

    class Logger {
        public:

            class LogLevel {
                public:
                    LogLevel(uint32_t level, Color::Modifier color, const char* sign);

                    Logger&         operator<<(Logger& in);
                    uint32_t        get_level() const;
                    char            get_sign()  const;
                    Color::Modifier get_color() const;

                protected:
                private:
                    LogLevel();
                    LogLevel(LogLevel& o);
                    LogLevel operator=(LogLevel o);

                    static std::vector<uint32_t> __level_collection;
                    uint32_t __level;
                    char __sign; 
                    Color::Modifier __color;
            };
            static Logger& getInstance();
            Logger& operator<<(bool value);
            Logger& operator<<(uint8_t value);
            Logger& operator<<(long value);
            Logger& operator<<(unsigned long value);
            Logger& operator<<(unsigned int value);
            Logger& operator<<(long long value);
            Logger& operator<<(unsigned long long value);
            Logger& operator<<(double value);
            Logger& operator<<(long double value);
            Logger& operator<<(const void* value);
            Logger& operator<<(const volatile void* value);
            Logger& operator<<(short value);
            Logger& operator<<(const signed int value);
            Logger& operator<<(const char* value);
            Logger& operator<<(const unsigned char* value);
            Logger& operator<<(const std::string& value);
            Logger& operator<<(_Setw __f);
            Logger& operator<<(const LogLevel& in);
            Logger& operator<<(Logger& (*__p_fun)(Logger&));
            template<typename T>
            Logger& operator<<(_Sbit<T> __f) {
                std::bitset<sizeof(T)*8> b_obj(__f._object);
                __msg << "b" << b_obj.to_string();
                __outWidth = 0;
                return *this;
            }
            template<typename T>
            Logger& operator<<(_SArray<T> __f) {
                for(uint32_t index = 0 ; index < __f._size; index++) {
                    __msg << std::setw(2) << std::setfill('0') << std::hex << (uint64_t)(__f._object[index]) << " ";
                }
                __outWidth = 0;
                return *this;
            }
            void setLogLevel(const LogLevel& in);
            friend Logger& hex(Logger& l);
            friend Logger& dec(Logger& l);
            friend Logger& endl(Logger& l);

            // basic_ostream& operator<<( /* extended-floating-point-type */ value );
            // basic_ostream& operator<<(std::basic_streambuf<CharT, Traits>* sb );
            // basic_ostream& operator<<(std::ios_base& (*func)(std::ios_base&) );
            // basic_ostream& operator<<(std::basic_ios<CharT, Traits>& (*func)(std::basic_ios<CharT, Traits>&) );
            // basic_ostream& operator<<(std::basic_ostream<CharT, Traits>& (*func)(std::basic_ostream<CharT, Traits>&) );
        protected:

        private:
            Logger();

            // Remove the ability to copy and assign
            Logger(const Logger&)            = delete;
            Logger& operator=(const Logger&) = delete;

            // Remove the ability to move
            Logger(Logger&&)            = delete;
            Logger& operator=(Logger&&) = delete;

            std::stringstream __msg;
            uint32_t __currentLogLevel = 0;
            uint32_t          __lastLogLevel;
            uint8_t           __outWidth;

            Logger& __flush();
    };

    extern Logger& logger;

    extern logger::Logger::LogLevel debug    ;//    = {10, Color::magenta,  "D"}; 
    extern logger::Logger::LogLevel info     ;//    = {20, Color::green,    "I"}; 
    extern logger::Logger::LogLevel warning  ;//    = {30, Color::yellow,   "W"}; 
    extern logger::Logger::LogLevel error    ;//    = {40, Color::red,      "E"}; 
    extern logger::Logger::LogLevel critical ;//    = {50, Color::bg_red,   "C"}; 

    Logger& hex(Logger& l);
    Logger& dec(Logger& l);
    Logger& endl(Logger& l);
};

#endif // LOGGER

