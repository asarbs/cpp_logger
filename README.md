# Logger Utility

A simple, flexible, and color-coded logging utility for C++ applications.

## Features

- Multiple log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL)
- Stream-based logging interface
- Color-coded output for better readability
- Easily configurable log level

## Files

- `logger.h`: Header file defining the Logger class and its functionalities.
- `logger.cpp`: Implementation of the Logger class.
- `color.h`: Header file for color definitions and utilities for terminal output.

## Usage

### Installation

To use the logger in your project, simply include the header files and compile the source file along with your project.


## Basic Example
```cpp
#include <iostream>
#include "logger.h"

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

```

### Run Example
type

<div style="color:white; background:black">
<code style="color:white; background:black">
$ make run </br>
Clean </br>
Build file: main.cpp -> main.o </br>
Build file: app </br>
Exe file: app </br>
2024-07-19 13:28:27.448274 <span style="color:purple"> [D] simple text </span></br>
2024-07-19 13:28:27.448343 <span style="color:purple"> [D] 12  AAA 0x </span></br>
2024-07-19 13:28:27.448363 <span style="color:green"> [I] cf 12.4 7fffffffffffffff </span></br>
2024-07-19 13:28:27.448371 <span style="color:green"> [I] 0xdeadbeef </span></br>
2024-07-19 13:28:27.448377 <span style="color:green"> [I] 0x000000de </span></br>
2024-07-19 13:28:27.448382 <span style="color:yellow"> [W] cf </span></br>
2024-07-19 13:28:27.448387 <span style="color:red"> [E] cf </span></br>
2024-07-19 13:28:27.448392 <span style="background-color: red"> [C] c f f A t </span></br>
</code>
</div>




## Log Levels
The logger supports the following log levels:

- DEBUG
- INFO
- WARNING
- ERROR
- CRITICAL

You can set the log level using `setLogLevel()` method:

```cpp
logger::logger.setLogLevel(logger::Logger::LogLevel::WARNING);
```

## Colored Output
The color.h file provides color modifiers to enhance the readability of log messages. Available colors include:

- Color::red
- Color::green
- Color::yellow
- Color::blue
- Color::magenta
- Color::reset (to reset to default color)

## Detailed Class and Method Documentation
`logger::Logger` **Class**
- **LogLevel**: Enum to define log levels (DEBUG, INFO, WARNING, ERROR, CRITICAL).
- **Logger()**: Constructor to initialize the logger.
- **operator<<**: Overloaded operator to handle different types of messages.
- **setLogLevel(LogLevel newLogLevel)**: Method to set the current log level.
- **end(logger::Logger& l)**: Ends the current log message and prints it if the log level is appropriate.
