// ExitCommand.cpp
#include "ExitCommand.hpp"
#include <iostream> // For std::cout

ExitCommand::ExitCommand(const std::string& name, Receiver& receiver): receiver(receiver), Command(name) {}

void ExitCommand::execute() {
    std::cout << "Exiting application...\n";
    exit(0);
}
