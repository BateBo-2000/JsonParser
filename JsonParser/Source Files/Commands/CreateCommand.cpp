#include "../../Header Files/Commands/CreateCommand.hpp"

CreateCommand::CreateCommand(ConsoleLogger& console, Receiver& receiver)
    : Command(), receiver(receiver), console(console) {}

void CreateCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Missing arguments.\nCommand syntax: create <path> <string>.");
    }
    else {
        if (args.size() > 3) {
            console.logWarning("Too many arguments.");
        }
        path = args[1];
        value = args[2];
    }
}

void CreateCommand::execute() {
    try
    {
        receiver.create(path, value);
        console.logInfo(path + " was created and set successfully and set to " + value + "." );
    }
    catch (const std::exception& e)
    {
        console.logError("Error while creating and setting " + path + " to value "+ value +". " + string(e.what()));
    }
}