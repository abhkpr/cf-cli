#include <iostream>
#include "commands/user.h"
#include "commands/contest.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: cf <command>\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "user") {
        if (argc < 3) {
            std::cout << "Usage: cf user <handle>\n";
            return 1;
        }
        get_user(argv[2]);

    } else if (command == "contest") {
        if (argc < 3) {
            std::cout << "Usage: cf contest <action>\n";
            return 1;
        }

        std::string action = argv[2];

        if (action == "list") {
            list_contests();
        } else {
            std::cout << "Unknown contest action\n";
        }

    } else {
        std::cout << "Unknown command\n";
    }

    return 0;
}
