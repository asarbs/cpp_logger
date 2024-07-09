#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <ostream>
#include <iomanip>
#include <chrono>


#include "color.h"

namespace logger{
    class Logger: public std::ostream {
        public:
            enum LogLevel {
            DEBUG = 10,
            INFO = 20,
            WARNING = 30,
            ERROR = 40,
            CRITICAL = 50,
            };

            Logger();

            Logger& operator<<(bool value) {
                
                __msg << (value == true ? "t" : "f");
                return *this;
            }
            Logger& operator<<(uint8_t value) {
                __msg << uint32_t(value);
                return *this;
            }
            Logger& operator<<(long value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(unsigned long value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(long long value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(unsigned long long value ) {
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(double value ) {
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(long double value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(const void* value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(const volatile void* value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(short value ){
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(const signed int value) {
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(const char* value) {
                
                __msg << value;
                return *this;
            }
            Logger& operator<<(const unsigned char* value) {
                
                __msg << value;
                return *this;
            }
            // std::ostream& operator<<(unsigned short value ){
                
            //     __msg << value;
            //     return *this;
            // }
            // std::ostream& operator<<(unsigned int value ){
                
            //     __msg << value;
            //     return *this;
            // }
            // std::ostream& operator<<(float value ){
                
            //     __msg << value;
            //     return *this;
            // }

            // basic_ostream& operator<<( /* extended-floating-point-type */ value );
            // basic_ostream& operator<<(std::basic_streambuf<CharT, Traits>* sb );
            // basic_ostream& operator<<(std::ios_base& (*func)(std::ios_base&) );
            // basic_ostream& operator<<(std::basic_ios<CharT, Traits>& (*func)(std::basic_ios<CharT, Traits>&) );
            // basic_ostream& operator<<(std::basic_ostream<CharT, Traits>& (*func)(std::basic_ostream<CharT, Traits>&) );

            Logger& operator<<(Logger& (*__p_fun)(Logger&)) {
                return __p_fun(*this);
            }

            static Logger& end(Logger& l);

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

            static void setLogLevel(LogLevel newLogLevel);

        protected:

        private:
            std::stringstream __msg;
            static LogLevel __currentLogLevel;
            LogLevel __lastLogLevel;
    };

    inline static Logger logger;
    
};

// template <typename T> std::basic_ostream& logger::Logger::operator<<(T const& value) {
//     const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
//     auto diff = now - this->_begin;
//     std::cout << std::setw(8) << duration_cast<std::chrono::nanoseconds>(diff).count() << ":" << std::setw(8) << this->_name << ":" << this->_mod << value << Color::reset << std::endl;
// }

// std::basic_ostream& operator<<( int value ) {
    
// }

#endif // LOGGER

