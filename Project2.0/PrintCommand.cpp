#include "PrintCommand.hpp"

PrintCommand::PrintCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void PrintCommand::execute() {
	try
	{
		const std::string& jsonContent = receiver.getJson();
		ConsoleLogger::logJson(jsonContent);
	}
	catch (const std::exception& e)
	{
		ConsoleLogger::logError("Error while printing: " + std::string(e.what()));
	}
}

void PrintCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) ConsoleLogger::logWarning(name + ": Too many arguments.");
    //no need for arguments
    //might be usefull in future
}
