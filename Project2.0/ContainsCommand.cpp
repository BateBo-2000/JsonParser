// ContainsCommand.cpp
#include "ContainsCommand.hpp"
#include <iostream>

ContainsCommand::ContainsCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void ContainsCommand::execute() {
    receiver.containsValue(json, value);
}
