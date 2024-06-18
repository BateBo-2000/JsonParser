// DeleteCommand.cpp
#include "DeleteCommand.hpp"
#include <iostream>

DeleteCommand::DeleteCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void DeleteCommand::execute() {
   
}
