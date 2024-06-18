#include "OpenCommand.hpp"
#include <stdexcept>

OpenCommand::OpenCommand(const std::string& name ,Receiver& receiver) : receiver(receiver), Command(name){}

void OpenCommand::setArguemnts(const std::vector<std::string>& args) {
    if (args.size() < 2) {
        throw std::invalid_argument("Missing arguments.");
    }else if (args.size() > 2) {
        //warning
        std::cerr << "Too many arguments." << std::endl;
    }
    filePath = args[1];
}

void OpenCommand::execute() {
    if (filePath.empty()) {
        std::cerr << "No file path provided." << std::endl;
        return;
    }
    receiver.readFile(filePath);
}
