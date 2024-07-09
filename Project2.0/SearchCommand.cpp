#include "SearchCommand.hpp"

SearchCommand::SearchCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

void SearchCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Missing arguments.\nCommand syntax: search <key>");
    }
    else{
        if (args.size() > 2) {
            //warning
            console.logWarning("Too many arguments.");
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
            console.logInfo("Coundn't find any results");
        }
        else {
            console.logJson(results);
        }
    }
    catch (const std::exception& e)
    {
        console.logError(string("Error while searching: ") + e.what());
    }
    
}
