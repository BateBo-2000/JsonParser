#include "../../Header Files/Commands/PrintCommand.hpp"

PrintCommand::PrintCommand(ConsoleLogger& console, Receiver& receiver)
    :Command(), receiver(receiver), console(console) {}

void PrintCommand::execute() {
	try
	{
		const std::string& jsonContent = receiver.getJson();
		console.logJson(jsonContent);
	}
	catch (const std::exception& e)
	{
		console.logError("Error while printing: " + std::string(e.what()));
	}
}

void PrintCommand::setArguments(const std::vector<std::string>& args) {
    if (args.size() > 1) console.logWarning("Too many arguments.");
    //no need for arguments
    //might be usefull in future
}
