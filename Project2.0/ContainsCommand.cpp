#include "ContainsCommand.hpp"

ContainsCommand::ContainsCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

void ContainsCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Missing arguments.");
    }
    else {
        if (args.size() > 2) {
            //warning
            console.logWarning("Too many arguments.");
        }
        searchValue = args[1];
    }
}

void ContainsCommand::execute() {
    std::string results;
    try
    {
        receiver.containsValue(searchValue, results);
        if (results.empty()) console.logInfo("Coundn't find any results that match "+searchValue);
        console.logJson(results);
    }
    catch (const std::exception& e)
    {
        console.logInfo("Error while searching: " + string(e.what()));
    }
}
