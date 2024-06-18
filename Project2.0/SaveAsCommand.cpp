// SaveAsCommand.cpp
#include "SaveAsCommand.hpp"
#include <iostream>

SaveAsCommand::SaveAsCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SaveAsCommand::execute() {
    receiver.saveJsonToFileAs(newFilePath);
}
