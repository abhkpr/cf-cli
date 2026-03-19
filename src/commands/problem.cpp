#include <iostream>
#include <string>
#include <vector>
#include <algorithm>      
#include "commands/problem.h"
#include "utils/cache.h"
#include "api/codeforces.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

#include <chrono> // for time checks

void get_problem(const std::string& code, const std::vector<std::string>& args) {
    std::string cache_path = std::string(getenv("HOME")) + "/.cf-cli/problems.json";

    bool refresh = std::find(args.begin(), args.end(), "--refresh") != args.end();

    bool fetch_from_api = refresh || !cache_exists(cache_path);

    // Auto refresh if cache is older than 12 hours
    if (!fetch_from_api) {
        auto last_mod = get_cache_time(cache_path);
        auto now = std::chrono::system_clock::now();
        auto age = std::chrono::duration_cast<std::chrono::hours>(now - last_mod).count();
        if (age >= 12) {
            fetch_from_api = true;
            std::cout << "Cache is older than 12h, refreshing...\n";
        }
    }

    std::string data;

    if (fetch_from_api) {
        std::cout << "Fetching problems from API...\n";
        data = http_get("https://codeforces.com/api/problemset.problems");
        write_cache(cache_path, data);
    } else {
        data = read_cache(cache_path);
    }

    // JSON parsing and problem lookup as before
    auto j = nlohmann::json::parse(data);
    bool found = false;
    for (auto &problem : j["result"]["problems"]) {
        std::string pid = std::to_string(problem["contestId"].get<int>()) + problem["index"].get<std::string>();
        if (pid == code) {
            std::cout << "Problem: " << problem["name"] << "\n";
            std::cout << "Rating: " << (problem.contains("rating") ? std::to_string(problem["rating"].get<int>()) : "N/A") << "\n";
            std::cout << "Tags: ";
            for (auto &tag : problem["tags"]) std::cout << tag.get<std::string>() << " ";
            std::cout << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        std::cout << "Problem not found.\n";
    }
}

void problem_command(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: cf problem <code> [--refresh]\n";
        return;
    }

    // Pass all args to get_problem so it can check for --refresh
    get_problem(args[1], args);
}
