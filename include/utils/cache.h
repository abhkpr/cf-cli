#pragma once
#include <string>
#include <chrono>

bool cache_exists(const std::string& path);
std::string read_cache(const std::string& path);
void write_cache(const std::string& path, const std::string& data);

// new function: get last modified time of file
std::chrono::system_clock::time_point get_cache_time(const std::string& path);
