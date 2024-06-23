#include "ExitCommand.hpp"

ExitCommand::ExitCommand(const std::string& name, Receiver& receiver): receiver(receiver), Command(name), forseExit(false) {}

void ExitCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) Logger::logWarning(name + ": Too many arguments.");
}

void ExitCommand::execute() {
    if (receiver.isChanged() && forseExit == false) {
        Logger::logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type the command again.");
        forseExit = true;
    }
    else {
        Logger::logInfo("Exiting application...");
        exit(0);
    }
}
