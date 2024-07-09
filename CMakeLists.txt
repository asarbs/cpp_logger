cmake_minimum_required(VERSION 3.10)

project(cpp_logger_lib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(cpp_logger_lib STATIC
    logger.cpp
    logger.h
)

target_compile_options(cpp_logger_lib PRIVATE -Wall -Wextra)

install(TARGETS cpp_logger_lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

export(TARGETS cpp_logger_lib FILE cpp_logger_lib-targets.cmake)
