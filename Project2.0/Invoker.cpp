#include "Invoker.hpp"
#include <iostream> // For std::cout and std::cerr
#include <stdexcept>

Invoker::Invoker() {}

Invoker::~Invoker() {
    for (Command* cmd : commandObjects) {
        delete cmd;
    }
}

void Invoker::registerCommand(Command* cmd) {
    if (cmd == nullptr) throw std::invalid_argument("Command cannot be nullptr.");
    commandObjects.push_back(cmd);
}

void Invoker::executeCommand(const std::string& commandLine) {
    std::vector<std::string> args;
    splitCommandLine(commandLine, args);
    if (args.empty()) {
        throw std::invalid_argument("Invalid argument/s.");
    }
    std::string& commandName = args[0];
    
    //find the command and invoke it
    for (size_t i = 0; i < commandObjects.size(); i++)
    {
        if (commandName == commandObjects[i]->getName()) {
            try
            {
                commandObjects[i]->setArguemnts(args);
                commandObjects[i]->execute();
                return;
            }
            catch (const std::exception& e)
            {
                throw std::runtime_error(e.what());
            }
        }
    }
    throw std::runtime_error("Command not found.");
}

size_t Invoker::getArgEnd(const std::string str, size_t start) {
    size_t end = 0;
    while (str[start + end] != ' ' && str[start + end] != '\0' && str[start + end] != '\n') {
        end++;
    }
    return end;
}

void Invoker::splitCommandLine(const std::string& commandLine, std::vector<std::string>& args) {
    size_t i = 0;
    while (commandLine[i] != '\0') {
        if (commandLine[i] == ' ') {
            i++;
        }
        else {
            size_t argEnd = getArgEnd(commandLine, i);
            args.push_back(commandLine.substr(i, argEnd));
            i += argEnd;
        }
    }
}
