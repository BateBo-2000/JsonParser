#include "SaveCommand.hpp"

SaveCommand::SaveCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

void SaveCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        throw std::invalid_argument("Missing arguments.\nCommand syntax: save [<path>]");
    }
    else if (args.size() == 1) {
        //default path
        filePath = receiver.getFileLocation();
        if(filePath.empty()) throw std::invalid_argument("Missing argument. File path has not been added yet.");
    }
    else{  
        if (args.size() > 2) {
            console.logWarning("Too many arguments.");
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
        console.logInfo(message);
    }
    else {
        console.logError(message);
    }
}

