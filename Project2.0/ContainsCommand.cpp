#include "ContainsCommand.hpp"

ContainsCommand::ContainsCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void ContainsCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument(name + ": Missing arguments.");
    }
    else {
        if (args.size() > 2) {
            //warning
            ConsoleLogger::logWarning(name + ": Too many arguments.");
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
