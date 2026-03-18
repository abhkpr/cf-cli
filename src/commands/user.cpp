#include "commands/user.h"
#include "api/codeforces.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void get_user(const std::string& handle) {
    std::string url = "https://codeforces.com/api/user.info?handles=" + handle;

    std::string data = http_get(url);
    auto j = json::parse(data);

    if (j["status"] != "OK") {
        std::cout << "Error fetching user\n";
        return;
    }

    auto user = j["result"][0];

    std::cout << "Handle: " << user["handle"] << "\n";
    std::cout << "Rating: " << user.value("rating", 0) << "\n";
    std::cout << "Rank: " << user.value("rank", "N/A") << "\n";
}

void user_command(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "Usage: cf user <handle>\n";
        return;
    }
    get_user(args[1]);
}
