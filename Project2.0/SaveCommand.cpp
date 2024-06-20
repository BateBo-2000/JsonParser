#include "SaveCommand.hpp"

SaveCommand::SaveCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SaveCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }
    else if (args.size() == 1) {
        //default path
        filePath = receiver.getFileLocation();
    }
    else{  
        if (args.size() > 2) {
            Logger::logWarning(name + ": Too many arguments.");
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
        throw std::invalid_argument(name + ": Invalid argument: File path is empty.");
    }
    bool success = receiver.writeFile(filePath, message);
    if (success) {
        Logger::logInfo(message);
    }
    else {
        Logger::logError(message);
    }
}

