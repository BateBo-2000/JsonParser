// SetCommand.cpp
#include "SetCommand.hpp"

SetCommand::SetCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SetCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        throw std::invalid_argument("Set/ Missing arguments.");
    }
    else {
        if (args.size() > 3) {
            //warning
            std::cerr << "Set/ Too many arguments." << std::endl;
        }
        path = args[1];
        value = args[2];
    }
}

void SetCommand::execute() {
    try
    {
        receiver.setJsonValue(path, value);
        std::cout << "Value " + value + " was set successfully to " + path+ "." << std::endl;
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(string("Error while setting value: ") + e.what());
    }
}