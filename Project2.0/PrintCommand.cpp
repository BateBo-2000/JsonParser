#include "PrintCommand.hpp"

PrintCommand::PrintCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void PrintCommand::execute() {
	try
	{
		receiver.printJson();
	}
	catch (const std::exception& e)
	{
		throw std::runtime_error(std::string("Error while printing: ") + e.what());
	}
}

void PrintCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() > 1) std::cerr << "Too many arguments." << std::endl;
    //no need for arguments
    //might be usefull in future
}
