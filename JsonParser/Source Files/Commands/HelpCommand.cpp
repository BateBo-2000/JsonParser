#include "../../Header Files/Commands/HelpCommand.hpp"

HelpCommand::HelpCommand(ConsoleLogger& console): console(console) {}

void HelpCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) console.logWarning("Too many arguments.");
}

void HelpCommand::execute() {
    console.logJson(USER_MAUAL);
}



