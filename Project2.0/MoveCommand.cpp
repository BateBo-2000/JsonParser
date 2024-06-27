#include "MoveCommand.hpp"

MoveCommand::MoveCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void MoveCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            //warning
            ConsoleLogger::logWarning(name + ": Too many arguments.");
        }
        from = args[1];
        to = args[2];
    }
}
void MoveCommand::execute() {
    try
    {
        receiver.move(from, to);
        ConsoleLogger::logInfo("Successfully moved to " + from + "\nto\n" + to);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Error while moving " + from + +"\nto\n" + to +":\n " + string(e.what()));
    }
}