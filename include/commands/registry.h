#pragma once
#include <string>
#include <vector>
#include <functional>
#include <map>

using CommandFunc = std::function<void(const std::vector<std::string>&)>;

class CommandRegistry {
public:
    void register_command(const std::string& name, CommandFunc func);
    void execute(const std::vector<std::string>& args);

private:
    std::map<std::string, CommandFunc> commands;
};
