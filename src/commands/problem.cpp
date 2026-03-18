#include "commands/problem.h"
#include "api/codeforces.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <cctype>

using json = nlohmann::json;

void get_problem(const std::string& code) {
    // Step 1: split contestId and index
    int i = 0;
    while (i < code.size() && isdigit(code[i])) i++;

    if (i == 0 || i == code.size()) {
        std::cout << "Invalid problem format\n";
        return;
    }

    int contestId = std::stoi(code.substr(0, i));
    std::string index = code.substr(i);

    // Step 2: fetch all problems
    std::string url = "https://codeforces.com/api/problemset.problems";
    std::string data = http_get(url);

    // Step 3: parse JSON
    auto j = json::parse(data);

    if (j["status"] != "OK") {
        std::cout << "Error fetching problems\n";
        return;
    }

    auto problems = j["result"]["problems"];

    // Step 4: search for problem
    for (auto& p : problems) {
        if (p["contestId"] == contestId && p["index"] == index) {
            std::cout << "Name: " << p["name"] << "\n";
            std::cout << "Contest: " << p["contestId"] << "\n";
            std::cout << "Index: " << p["index"] << "\n";

            if (p.contains("rating"))
                std::cout << "Rating: " << p["rating"] << "\n";

            std::cout << "Tags: ";
            for (auto& tag : p["tags"])
                std::cout << tag << " ";
            std::cout << "\n";

            return;
        }
    }

    std::cout << "Problem not found\n";
}

void problem_command(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: cf problem <id>\n";
        return;
    }
    get_problem(args[1]);
}
