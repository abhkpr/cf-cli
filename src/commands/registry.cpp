#include "commands/registry.h"
#include <iostream>

void CommandRegistry::register_command(const std::string& name, CommandFunc func) {
    commands[name] = func;
}

void CommandRegistry::execute(const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "No command provided\n";
        return;
    }

    std::string command = args[0];

    if (commands.find(command) != commands.end()) {
        commands[command](args);
    } else {
        std::cout << "Unknown command\n";
    }
}
