#include "ExitCommand.hpp"

ExitCommand::ExitCommand(const std::string& name, Receiver& receiver): receiver(receiver), Command(name) {}

void ExitCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() > 1) Logger::logWarning(name + ": Too many arguments.");
    //no need for arguments
    //might be usefull in future
}

void ExitCommand::execute() {
    Logger::logInfo("Exiting application...");
    exit(0);
}
