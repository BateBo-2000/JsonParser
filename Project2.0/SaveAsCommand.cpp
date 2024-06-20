#include "SaveAsCommand.hpp"

SaveAsCommand::SaveAsCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

//helper function
void SaveAsCommand::changeName(std::string& path, const std::string& newName) {
    size_t nameStart = path.find_last_of('\\');
    std::string updatedName = newName;

    if (updatedName.find('.') == std::string::npos) {
        updatedName += ".json";
    }

    if (nameStart == std::string::npos || nameStart != path.length() - 1) {
        path += "\\";
    }

    path += updatedName;
}

void SaveAsCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument(name+": Missing arguments.");
    }
    else if (args.size() == 2) {
        //default path
        newFilePath = receiver.getFileLocation();
        changeName(newFilePath, args[1]);
    }
    else {
        if (args.size() > 3) {
            Logger::logWarning(name + ": Too many arguments.");
        }
        try
        {
            newFilePath = args[2];
            changeName(newFilePath, args[1]);
        }
        catch (const std::exception& e)
        {
            throw e;
        }

    }
}

void SaveAsCommand::execute() {
    std::string message;

    if (newFilePath.empty()) {
        throw std::invalid_argument(name + ": Invalid argument: File path is empty.");
    }
    bool success = receiver.writeFile(newFilePath, message);
    if (success) {
        Logger::logInfo(message);
    }
    else {
        Logger::logError(message);
    }
}



