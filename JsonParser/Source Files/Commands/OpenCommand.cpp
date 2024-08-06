#include "../../Header Files/Commands/OpenCommand.hpp"

OpenCommand::OpenCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console), dontSave(false){}

void OpenCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw CommandException("Missing arguments.\nCommand syntax: open <path>");
    }else if (args.size() > 2) {
        //warning
        console.logWarning("Too many arguments.");
    }
    filePath = args[1];
}

void OpenCommand::execute() {
    if (filePath.empty()) {
        throw CommandException("Invalid argument: File path is empty.");
    }
    if (receiver.isChanged() && dontSave == false) {
        console.logWarning("Are you sure you dont want to save the changes?\nIf you want to exit without saving type the command again.");
        dontSave = true;
    }
    else {
        try
        {
            receiver.loadFile(filePath);
            console.logInfo("File opened successfully: "+ filePath);
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
}
