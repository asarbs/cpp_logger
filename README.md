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

```cpp
#include "logger.h"
#include "color.h"
```

## Basic Example
```cpp
#include <iostream>
#include "logger.h"
#include "color.h"

int main() {
    logger::Logger log;

    log.setLogLevel(logger::Logger::DEBUG);

    log << logger::Logger::INFO << "This is an info message." << logger::Logger::end;
    log << logger::Logger::WARNING << Color::yellow << "This is a warning message." << Color::reset << logger::Logger::end;
    log << logger::Logger::ERROR << Color::red << "This is an error message." << Color::reset << logger::Logger::end;

    return 0;
}

```

## Log Levels
The logger supports the following log levels:

- DEBUG
- INFO
- WARNING
- ERROR
- CRITICAL
You can set the log level using `setLogLevel()` method:

```cpp
log.setLogLevel(logger::Logger::LogLevel::WARNING);
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
