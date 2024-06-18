#include "ValidateCommand.hpp"
#include <iostream>

ValidateCommand::ValidateCommand(const std::string& name, Receiver& receiver)
    : receiver(receiver), Command(name) {}

void ValidateCommand::execute() {
    if (receiver.isValidJson()) {
        std::cout << "JSON is valid." << std::endl;
    }
    else {
        std::cerr << "JSON is not valid." << std::endl;
    }
}

void ValidateCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() > 1) std::cerr << "Too many arguments."<< std::endl;
    //no need for arguments
    //might be usefull in future
}