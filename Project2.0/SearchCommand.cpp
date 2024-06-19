// SearchCommand.cpp
#include "SearchCommand.hpp"
#include <iostream>

SearchCommand::SearchCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void SearchCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Search/ Missing arguments.");
    }
    else{
        if (args.size() > 2) {
            //warning
            std::cerr << "Search/ Too many arguments." << std::endl;
        }
        searchKey = args[1];
    }
}

void SearchCommand::execute() {
    std::string results;
    try
    {
        receiver.searchJson(searchKey, results);
        if (results.empty()) std::cout << "Coundn't find any results";
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(string("Error while searching: ") + e.what());
    }
    std::cout << results << std::endl;
    
}
