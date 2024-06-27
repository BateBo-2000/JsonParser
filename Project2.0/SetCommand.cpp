#include "SetCommand.hpp"

SetCommand::SetCommand(Receiver& receiver)
    : Command(), receiver(receiver) {}

void SetCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            //warning
            ConsoleLogger::logWarning("Too many arguments.");
        }
        path = args[1];
        value = args[2];
    }
}

void SetCommand::execute() {
    try
    {
        receiver.setJsonValue(path, value);
        ConsoleLogger::logInfo(path + " was set successfully and set to " + value + ".");
    }
    catch (const std::exception& e)
    {
        ConsoleLogger::logError("Error while setting value " + value + " to path " + path + ". " + string(e.what()));
    }
}