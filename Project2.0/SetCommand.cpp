// SetCommand.cpp
#include "SetCommand.hpp"
#include <iostream>

SetCommand::SetCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SetCommand::execute() {
    
}