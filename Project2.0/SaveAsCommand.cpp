// SaveAsCommand.cpp
#include "SaveAsCommand.hpp"
#include <iostream>

SaveAsCommand::SaveAsCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

//helper function
void changeName(std::string& path, const std::string& newName) {
    // for now doesn't support Unix's "/"
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

void SaveAsCommand::execute() {
    try
    {
        if (newFilePath == "") throw std::invalid_argument("Save/Invalid argument/ File path is empty.");
        receiver.writeFile(newFilePath);
    }
    catch (const std::exception& e)
    {
        throw e;
    }
}

void SaveAsCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Save/ Missing arguments.");
    }
    else if (args.size() == 2) {
        //default path
        newFilePath = receiver.getFileLocation();
        changeName(newFilePath, args[1]);
    }
    else {
        if (args.size() > 3) {
            //warning
            std::cerr << "Save/ Too many arguments." << std::endl;
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

