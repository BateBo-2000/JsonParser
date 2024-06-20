#include "ExitCommand.hpp"

ExitCommand::ExitCommand(const std::string& name, Receiver& receiver): receiver(receiver), Command(name), forseExit(false) {}

void ExitCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 2) Logger::logWarning(name + ": Too many arguments.");
    if (args.size() == 2 && args[1] == name) forseExit = true;
    if (args.size() == 1) forseExit = false;
}

void ExitCommand::execute() {
    if (receiver.isChanged() && forseExit == false) {
        Logger::logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type \""+name+" "+ name+ "\".");
    }
    else {
        Logger::logInfo("Exiting application...");
        exit(0);
    }
}
