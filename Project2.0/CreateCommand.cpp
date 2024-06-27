#include "CreateCommand.hpp"

CreateCommand::CreateCommand(Receiver& receiver)
    : Command(), receiver(receiver) {}

void CreateCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            ConsoleLogger::logWarning("Too many arguments.");
        }
        path = args[1];
        value = args[2];
    }
}

void CreateCommand::execute() {
    try
    {
        receiver.create(path, value);
        ConsoleLogger::logInfo(path + " was created and set successfully and set to " + value + "." );
    }
    catch (const std::exception& e)
    {
        ConsoleLogger::logError("Error while creating and setting " + path + " to value "+ value +". " + string(e.what()));
    }
}