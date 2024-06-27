#include "ExitCommand.hpp"

ExitCommand::ExitCommand(Receiver& receiver): Command(), receiver(receiver), forseExit(false) {}

void ExitCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) ConsoleLogger::logWarning("Too many arguments.");
}

void ExitCommand::execute() {
    if (receiver.isChanged() && forseExit == false) {
        ConsoleLogger::logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type the command again.");
        forseExit = true;
    }
    else {
        ConsoleLogger::logInfo("Exiting application...");
        exit(0);
    }
}
