// SaveCommand.cpp
#include "SaveCommand.hpp"
#include <iostream>

SaveCommand::SaveCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SaveCommand::execute() {
    receiver.saveJsonToFile(filePath);
}
