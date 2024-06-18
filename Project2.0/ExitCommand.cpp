// ExitCommand.cpp
#include "ExitCommand.hpp"
#include <iostream> // For std::cout

ExitCommand::ExitCommand(const std::string& name, Receiver& receiver): receiver(receiver), Command(name) {}

void ExitCommand::setArguemnts(const std::vector<std::string>& args) {
    //no need for arguments
    //might be usefull in future
}

void ExitCommand::execute() {
    std::cout << "Exiting application...\n";
    exit(0);
}
