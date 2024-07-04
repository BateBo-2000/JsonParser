#include "ValidateCommand.hpp"

ValidateCommand::ValidateCommand(ConsoleLogger& console, Receiver& receiver)
    : Command(), receiver(receiver), console(console) {}

void ValidateCommand::execute() {
    std::string errorMsg;
    if (receiver.isValidJson(errorMsg)) {
        if (errorMsg != "") console.logInfo(errorMsg);
        console.logInfo("JSON is valid.");
    }
    else {
        console.logError("JSON is not valid.\n" + errorMsg);
    }
}

void ValidateCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) console.logWarning("Too many arguments.");
    //no need for arguments
    //might be usefull in future
}