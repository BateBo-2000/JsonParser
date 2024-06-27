#include "SaveCommand.hpp"

SaveCommand::SaveCommand(Receiver& receiver)
    :Command(), receiver(receiver) {}

void SaveCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        throw std::invalid_argument("Missing arguments.");
    }
    else if (args.size() == 1) {
        //default path
        filePath = receiver.getFileLocation();
    }
    else{  
        if (args.size() > 2) {
            ConsoleLogger::logWarning("Too many arguments.");
        }
        try
        {
            filePath = args[1];
        }
        catch (const std::exception& e)
        {
            throw e;
        }
        
    }
}

void SaveCommand::execute() {
    std::string message;

    if (filePath.empty()) {
        throw std::invalid_argument("Invalid argument: File path is empty.");
    }
    bool success = receiver.writeFile(filePath, message);
    if (success) {
        ConsoleLogger::logInfo(message);
    }
    else {
        ConsoleLogger::logError(message);
    }
}

