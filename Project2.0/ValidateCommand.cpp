#include "ValidateCommand.hpp"
#include "Logger.hpp"
#include <iostream>

ValidateCommand::ValidateCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void ValidateCommand::execute() {
    std::string errorMsg;
    if (receiver.isValidJson(&errorMsg)) {
        Logger::logInfo("JSON is valid.");
    }
    else {
        Logger::logError("JSON is not valid.");
        if (!errorMsg.empty()) std::cerr << errorMsg << std::endl;
    }
}

void ValidateCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() > 1) Logger::logWarning(name + ": Too many arguments.");
    //no need for arguments
    //might be usefull in future
}