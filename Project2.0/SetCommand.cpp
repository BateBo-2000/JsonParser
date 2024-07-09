#include "SetCommand.hpp"

SetCommand::SetCommand(ConsoleLogger& console, Receiver& receiver)
    : Command(), receiver(receiver), console(console) {}

void SetCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Missing arguments.\nCommand syntax: set <path> <string>");
    }
    else {
        if (args.size() > 3) {
            //warning
            console.logWarning("Too many arguments.");
        }
        path = args[1];
        value = args[2];
    }
}

void SetCommand::execute() {
    try
    {
        receiver.setJsonValue(path, value);
        console.logInfo(path + " was set successfully and set to " + value + ".");
    }
    catch (const std::exception& e)
    {
        console.logError("Error while setting value " + value + " to path " + path + ". " + string(e.what()));
    }
}