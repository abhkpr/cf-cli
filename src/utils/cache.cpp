#include "utils/cache.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>

bool cache_exists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

std::string read_cache(const std::string& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void write_cache(const std::string& path, const std::string& data) {
    std::ofstream file(path);
    file << data;
}

std::chrono::system_clock::time_point get_cache_time(const std::string& path) {
    struct stat result;
    if (stat(path.c_str(), &result) == 0) {
        auto mod_time = result.st_mtime;
        return std::chrono::system_clock::from_time_t(mod_time);
    }
    // If file does not exist, return epoch
    return std::chrono::system_clock::from_time_t(0);
}
