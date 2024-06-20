#include "ApplicationController.hpp"
#include "OpenCommand.hpp"
#include "PrintCommand.hpp"
#include "SaveCommand.hpp"
#include "SaveAsCommand.hpp"
#include "ExitCommand.hpp"
#include "ValidateCommand.hpp"
#include "SearchCommand.hpp"
#include "DeleteCommand.hpp"
#include "ContainsCommand.hpp"
#include "SetCommand.hpp"
#include "CreateCommand.hpp"
#include "MoveCommand.hpp"

AppController::AppController() {
    //Register commands with the Invoker
    try
    {
        invoker.registerCommand(new(std::nothrow) OpenCommand("open", jsonEditor));
        invoker.registerCommand(new(std::nothrow) PrintCommand("print", jsonEditor));
        invoker.registerCommand(new(std::nothrow) SaveCommand("save", jsonEditor));
        invoker.registerCommand(new(std::nothrow) SaveAsCommand("saveas", jsonEditor));
        invoker.registerCommand(new(std::nothrow) ExitCommand("exit", jsonEditor));
        invoker.registerCommand(new(std::nothrow) ValidateCommand("validate", jsonEditor));
        invoker.registerCommand(new(std::nothrow) SearchCommand("search", jsonEditor));
        invoker.registerCommand(new(std::nothrow) DeleteCommand("delete", jsonEditor));
        invoker.registerCommand(new(std::nothrow) ContainsCommand("contains", jsonEditor));
        invoker.registerCommand(new(std::nothrow) SetCommand("set", jsonEditor));
        invoker.registerCommand(new(std::nothrow) CreateCommand("create", jsonEditor));
        invoker.registerCommand(new(std::nothrow) MoveCommand("move", jsonEditor));
    }
    catch (const std::invalid_argument&)
    {
        std::cout << "Couldn't setup all commands properly. \nPlease restart the app." << std::endl;
    } 
}

void AppController::run() {
    std::string commandLine;

    do {
        std::cout << "\nEnter a command: ";
        std::getline(std::cin, commandLine);
        processCommand(commandLine);
    } while (commandLine != "exit");
}

void AppController::processCommand(const std::string& commandLine) {
    try
    {
        invoker.executeCommand(commandLine);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
