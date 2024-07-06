#include "MoveCommand.hpp"

MoveCommand::MoveCommand(ConsoleLogger& console, Receiver& receiver)
    : Command(), receiver(receiver), console(console) {}

void MoveCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            //warning
            console.logWarning("Too many arguments.");
        }
        from = args[1];
        to = args[2];
    }
}
void MoveCommand::execute() {
    if (from == to) {
        console.logWarning("Nothing has been moved.");
        return;
    }
    try
    {
        receiver.move(from, to);
        console.logInfo("Successfully moved to " + from + "\nto\n" + to);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Error while moving " + from + +"\nto\n" + to +":\n " + string(e.what()));
    }
}