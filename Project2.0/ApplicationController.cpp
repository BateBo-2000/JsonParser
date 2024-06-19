#include "ApplicationController.hpp"
#include "OpenCommand.hpp"
#include "PrintCommand.hpp"
#include "SaveCommand.hpp"
#include "SaveAsCommand.hpp"
#include "ExitCommand.hpp"
#include "ValidateCommand.hpp"
#include "SearchCommand.hpp"
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
    }
    catch (const std::invalid_argument& e)
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
