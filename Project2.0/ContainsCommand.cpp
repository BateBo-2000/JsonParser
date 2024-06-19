// ContainsCommand.cpp
#include "ContainsCommand.hpp"
#include <iostream>

ContainsCommand::ContainsCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void ContainsCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Conatins/ Missing arguments.");
    }
    else {
        if (args.size() > 2) {
            //warning
            std::cerr << "Conatins/ Too many arguments." << std::endl;
        }
        searchValue = args[1];
    }
}

void ContainsCommand::execute() {
    std::string results;
    try
    {
        receiver.containsValue(searchValue, results);
        if (results.empty()) std::cout << "Coundn't find any results";
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(string("Error while searching: ") + e.what());
    }
    std::cout << results << std::endl;
}
