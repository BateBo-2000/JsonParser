#include "../../Header Files/Commands/SaveCommand.hpp"

SaveCommand::SaveCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

void SaveCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        throw CommandException("Missing arguments.\nCommand syntax: save [<path>]");
    }
    else if (args.size() == 1) {
        //default path
        filePath = receiver.getFileLocation();
        if(filePath.empty()) throw CommandException("Missing argument. File path has not been added yet.");
    }
    else{  
        if (args.size() > 2) {
            console.logWarning("Too many arguments.");
        }
        filePath = args[1];
    }
}

void SaveCommand::execute() {
    if (filePath.empty()) {
        throw CommandException("Invalid argument: File path is empty.");
    }

    try
    {
        receiver.writeFile(filePath);
        console.logInfo("JSON saved to file: "+ filePath);
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

