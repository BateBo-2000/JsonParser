#include "SearchCommand.hpp"

SearchCommand::SearchCommand(Receiver& receiver)
    :Command(), receiver(receiver)  {}

void SearchCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Missing arguments.");
    }
    else{
        if (args.size() > 2) {
            //warning
            ConsoleLogger::logWarning("Too many arguments.");
        }
        searchKey = args[1];
    }
}

void SearchCommand::execute() {
    std::string results;
    try
    {
        receiver.searchJson(searchKey, results);
        if (results.empty()) {
            ConsoleLogger::logInfo("Coundn't find any results");
        }
        else {
            ConsoleLogger::logJson(results);
        }
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(string("Error while searching: ") + e.what());
    }
    
}
