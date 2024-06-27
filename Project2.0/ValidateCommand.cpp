#include "ValidateCommand.hpp"

ValidateCommand::ValidateCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void ValidateCommand::execute() {
    std::string errorMsg;
    if (receiver.isValidJson(&errorMsg)) {
        ConsoleLogger::logInfo("JSON is valid.");
    }
    else {
        ConsoleLogger::logError("JSON is not valid.\n" + errorMsg);
    }
}

void ValidateCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) ConsoleLogger::logWarning(name + ": Too many arguments.");
    //no need for arguments
    //might be usefull in future
}