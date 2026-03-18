#include "commands/registry.h"
#include "commands/user.h"
#include "commands/contest.h"
#include "commands/problem.h"

int main(int argc, char* argv[]) {
    CommandRegistry registry;

    // register commands
    registry.register_command("user", user_command);
    registry.register_command("contest", contest_command);
    registry.register_command("problem", problem_command);

    // convert argv → vector
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
        args.push_back(argv[i]);
    }

    registry.execute(args);

    return 0;
}
