#include "DeleteCommand.hpp"

DeleteCommand::DeleteCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void DeleteCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }
    else {
        if (args.size() > 2) {
            //warning
            ConsoleLogger::logWarning(name + ": Too many arguments.");
        }
        path = args[1];
    }
}

void DeleteCommand::execute() {
    try {
        receiver.deleteJsonValue(path);
        ConsoleLogger::logInfo(path+" was deleted and successfully.");
    }
    catch (const std::exception& e) {
        ConsoleLogger::logError(std::string("Exception caught: ") + e.what());
    }
}
