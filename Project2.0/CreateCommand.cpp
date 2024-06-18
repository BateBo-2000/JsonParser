// CreateCommand.cpp
#include "CreateCommand.hpp"
#include <iostream>

CreateCommand::CreateCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void CreateCommand::execute() {
    receiver.createJsonValue(path, value);
}
