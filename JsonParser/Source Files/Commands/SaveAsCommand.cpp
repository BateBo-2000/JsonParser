#include "../../Header Files/Commands/SaveAsCommand.hpp"

SaveAsCommand::SaveAsCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

//helper function
void SaveAsCommand::changeName(std::string& path, const std::string& newName) {
    //add extention
    std::string updatedName = newName;
    if (updatedName.find('.') == std::string::npos) {
        updatedName += ".json";
    }
    //remove the old name
    size_t oldNameStart = path.find_last_of('\\');
    path = path.substr(0,oldNameStart);

    //add the new name
    path += updatedName;
}

void SaveAsCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw CommandException("Missing arguments.\nCommand syntax: saveas <file> [<path>]");
    }
    else if (args.size() == 2) {
        //default path
        newFilePath = receiver.getFileLocation();
        if (newFilePath.empty()) throw CommandException("Missing argument. File path has not been added yet.");
        changeName(newFilePath, args[1]);
    }
    else {
        if (args.size() > 3) {
            console.logWarning("Too many arguments.");
        }
        newFilePath = args[2];
        changeName(newFilePath, args[1]);
    }
}

void SaveAsCommand::execute() {
    if (newFilePath.empty()) {
        throw CommandException("Invalid argument: File path is empty.");
    }

    try
    {
        receiver.writeFile(newFilePath);
        console.logInfo("JSON saved to file: " + newFilePath);
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



