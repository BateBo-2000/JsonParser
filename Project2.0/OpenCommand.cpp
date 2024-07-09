#include "OpenCommand.hpp"

OpenCommand::OpenCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console), dontSave(false){}

void OpenCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Missing arguments.\nCommand syntax: open <path>");
    }else if (args.size() > 2) {
        //warning
        console.logWarning("Too many arguments.");
    }
    filePath = args[1];
}

void OpenCommand::execute() {
    std::string message;
    if (filePath.empty()) {
        throw std::invalid_argument("Invalid argument: File path is empty.");
    }
    if (receiver.isChanged() && dontSave == false) {
        console.logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type the command again.");
        dontSave = true;
    }
    else {
        bool success = receiver.loadFile(filePath, message);
        if (success) {
            console.logInfo(message);
        }
        else {
            console.logError(message);
        }
    }
}
