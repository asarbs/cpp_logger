#include "logger.h"


std::vector<uint32_t> logger::Logger::LogLevel::__level_collection = std::vector<uint32_t>();

logger::Logger::LogLevel logger::debug      = {10, Color::magenta,  "D"}; 
logger::Logger::LogLevel logger::info       = {20, Color::green,    "I"}; 
logger::Logger::LogLevel logger::warning    = {30, Color::yellow,   "W"}; 
logger::Logger::LogLevel logger::error      = {40, Color::red,      "E"}; 
logger::Logger::LogLevel logger::critical   = {50, Color::bg_red,   "C"}; 
