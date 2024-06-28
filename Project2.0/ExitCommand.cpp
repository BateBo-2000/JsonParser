#include "ExitCommand.hpp"

ExitCommand::ExitCommand(ConsoleLogger& console, Receiver& receiver): Command(), receiver(receiver), console(console), forseExit(false) {}

void ExitCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) console.logWarning("Too many arguments.");
}

void ExitCommand::execute() {
    if (receiver.isChanged() && forseExit == false) {
        console.logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type the command again.");
        forseExit = true;
    }
    else {
        console.logInfo("Exiting application...");
        exit(0);
    }
}
