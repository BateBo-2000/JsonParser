// SearchCommand.cpp
#include "SearchCommand.hpp"
#include <iostream>

SearchCommand::SearchCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SearchCommand::execute() {
    receiver.searchJson(json, key);
}
