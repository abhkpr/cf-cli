#include "commands/problem.h"
#include "commands/dispatcher.h"
#include "commands/user.h"
#include "commands/contest.h"
#include <iostream>
#include <unordered_map>

void dispatch_command(const std::vector<std::string>& args) {
    if (args.size() == 0) {
        std::cout << "No command provided\n";
        return;
    }

    std::string command = args[0];

    if (command == "user") {
        if (args.size() < 2) {
            std::cout << "Usage: cf user <handle>\n";
            return;
        }
        get_user(args[1]);

    } else if (command == "contest") {
        if (args.size() < 2) {
            std::cout << "Usage: cf contest <action>\n";
            return;
        }

        std::string action = args[1];

        if (action == "list") {
            list_contests();
        } else {
            std::cout << "Unknown contest action\n";
        }

    } else if (command == "problem") {
        if (args.size() < 2) {
            std::cout << "Usage: cf problem <id>\n";
            return;
        }
        get_problem(args[1]);

    } else {
        std::cout << "Unknown command\n";
    }
}
