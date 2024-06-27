#include "OpenCommand.hpp"

OpenCommand::OpenCommand(const std::string& name ,Receiver& receiver) : receiver(receiver), Command(name), dontSave(false){}

void OpenCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }else if (args.size() > 2) {
        //warning
        ConsoleLogger::logWarning(name + ": Too many arguments.");
    }
    filePath = args[1];
}

void OpenCommand::execute() {
    std::string message;
    if (filePath.empty()) {
        throw std::invalid_argument(name+ ": Invalid argument: File path is empty.");
    }
    if (receiver.isChanged() && dontSave == false) {
        ConsoleLogger::logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type the command again.");
        dontSave = true;
    }
    else {
        bool success = receiver.loadFile(filePath, message);
        if (success) {
            ConsoleLogger::logInfo(message);
        }
        else {
            ConsoleLogger::logError(message);
        }
    }
}
