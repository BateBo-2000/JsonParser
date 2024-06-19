// SaveCommand.cpp
#include "SaveCommand.hpp"

SaveCommand::SaveCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SaveCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 1) {
        throw std::invalid_argument("Save/ Missing arguments.");
    }
    else if (args.size() == 1) {
        //default path
        filePath = receiver.getFileLocation();
    }
    else{  
        if (args.size() > 2) {
            //warning
            std::cerr << "Save/ Too many arguments." << std::endl;
        }
        try
        {
            filePath = args[1];
        }
        catch (const std::exception& e)
        {
            throw e;
        }
        
    }
}

void SaveCommand::execute() {
    try
    {
        //dont throw print
        if (filePath == "") throw std::invalid_argument("Save/Invalid argument/ File path is empty.");
        receiver.writeFile(filePath);
    }
    catch (const std::exception& e)
    {
        throw e;
    }
}

