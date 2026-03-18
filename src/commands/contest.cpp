#include "commands/contest.h"
#include "api/codeforces.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void list_contests() {
    std::string url = "https://codeforces.com/api/contest.list";

    std::string data = http_get(url);
    auto j = json::parse(data);

    if (j["status"] != "OK") {
        std::cout << "Error fetching contests\n";
        return;
    }

    auto contests = j["result"];

    // Show only first 10 (don’t spam terminal)
    for (int i = 0; i < 10 && i < contests.size(); i++) {
        auto c = contests[i];

        std::cout << c["id"] << " | "
                  << c["name"] << " | "
                  << c["phase"] << "\n";
    }
}
