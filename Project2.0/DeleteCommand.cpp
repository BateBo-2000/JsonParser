// DeleteCommand.cpp
#include "DeleteCommand.hpp"
#include <iostream>

DeleteCommand::DeleteCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void DeleteCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Delete/ Missing arguments.");
    }
    else {
        if (args.size() > 2) {
            //warning
            std::cerr << "Delete/ Too many arguments." << std::endl;
        }
        path = args[1];
    }
}

void DeleteCommand::execute() {
    try
    {
        receiver.deleteJsonValue(path);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(string("Error while deleting: ") + e.what());
    }
}
