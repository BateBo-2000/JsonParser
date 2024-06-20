// SetCommand.cpp
#include "SetCommand.hpp"
#include "Logger.hpp"

SetCommand::SetCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SetCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            //warning
            Logger::logWarning(name + ": Too many arguments.");
        }
        path = args[1];
        value = args[2];
    }
}

void SetCommand::execute() {
    try
    {
        receiver.setJsonValue(path, value);
        Logger::logInfo(path + " was set successfully and set to " + value + ".");
    }
    catch (const std::exception& e)
    {
        Logger::logError("Error while setting value " + value + " to path " + path + string(e.what()));
    }
}