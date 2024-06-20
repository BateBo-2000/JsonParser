#include "OpenCommand.hpp"
#include "Logger.hpp"
#include <stdexcept>

OpenCommand::OpenCommand(const std::string& name ,Receiver& receiver) : receiver(receiver), Command(name){}

void OpenCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }else if (args.size() > 2) {
        //warning
        Logger::logWarning(name + ": Too many arguments.");
    }
    filePath = args[1];
}

void OpenCommand::execute() {
    std::string message;
    if (filePath.empty()) {
        throw std::invalid_argument(name+ ": Invalid argument: File path is empty.");
    }
    bool success = receiver.loadFile(filePath, message);
    if (success) {
        Logger::logInfo(message);
    }
    else {
        Logger::logError(message); 
    }
}
