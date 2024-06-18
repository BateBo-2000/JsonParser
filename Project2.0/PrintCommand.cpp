#include "PrintCommand.hpp"

PrintCommand::PrintCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void PrintCommand::execute() {
    receiver.printJson();
}

void PrintCommand::setArguemnts(const std::vector<std::string>& args) {
    //no need for arguments
    //might be usefull in future
}
