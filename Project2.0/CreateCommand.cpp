// CreateCommand.cpp
#include "CreateCommand.hpp"
#include <iostream>

CreateCommand::CreateCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void CreateCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Create/ Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            //warning
            std::cerr << "Create/ Too many arguments." << std::endl;
        }
        path = args[1];
        value = args[2];
    }
}

void CreateCommand::execute() {
    try
    {
        receiver.create(path, value);
        std::cout << path + " was created and set successfully and set to " + value + "." << std::endl;
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(string("Error while creating and setting " + path + ": ") + e.what());
    }
}