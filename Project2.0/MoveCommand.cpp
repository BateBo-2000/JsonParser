// MoveCommand.cpp
#include "MoveCommand.hpp"
#include <iostream>

MoveCommand::MoveCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void MoveCommand::execute() {
    receiver.moveJsonValue(from, to);
}