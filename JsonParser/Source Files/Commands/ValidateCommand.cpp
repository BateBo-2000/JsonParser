#include "../../Header Files/Commands/ValidateCommand.hpp"

ValidateCommand::ValidateCommand(ConsoleLogger& console, Receiver& receiver)
    : Command(), receiver(receiver), console(console) {}

void ValidateCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) console.logWarning("Too many arguments.");
    //no need for arguments
    //might be usefull in future
}

void ValidateCommand::execute() {
    try
    {
        bool data = receiver.isValidJson();
        console.logInfo("JSON is valid.");
    }
    catch (const ParsingError& e)
    {
        console.logInfo("JSON is not valid.\n" + string(e.what()));
    }
    catch (const ReceiverException& e)
    {
        console.logError(e.what());
    }
    catch (const std::exception&)
    {
        console.logError("Something went wrong!");
    }
}

