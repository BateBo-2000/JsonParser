#include "ContainsCommand.hpp"

ContainsCommand::ContainsCommand(Receiver& receiver)
    :Command(), receiver(receiver) {}

void ContainsCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Missing arguments.");
    }
    else {
        if (args.size() > 2) {
            //warning
            ConsoleLogger::logWarning("Too many arguments.");
        }
        searchValue = args[1];
    }
}

void ContainsCommand::execute() {
    std::string results;
    try
    {
        receiver.containsValue(searchValue, results);
        if (results.empty()) ConsoleLogger::logInfo("Coundn't find any results that match "+searchValue);
        ConsoleLogger::logJson(results);
    }
    catch (const std::exception& e)
    {
        ConsoleLogger::logInfo("Error while searching: " + string(e.what()));
    }
}
