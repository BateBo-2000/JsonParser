#include "../../Header Files/Commands/DeleteCommand.hpp"

DeleteCommand::DeleteCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

void DeleteCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw CommandException("Missing arguments.\nCommand syntax: delete <path>");
    }
    else {
        if (args.size() > 2) {
            //warning
            console.logWarning("Too many arguments.");
        }
        path = args[1];
    }
}

void DeleteCommand::execute() {
    try {
        receiver.deleteJsonValue(path);
        console.logInfo(path+" was deleted and successfully.");
    }
    catch (const std::exception& e) {
        console.logError(std::string("Exception caught: ") + e.what());
    }
}
