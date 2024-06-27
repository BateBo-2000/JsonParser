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
        invoker.registerCommand("open", new OpenCommand(jsonEditor));
        invoker.registerCommand("print", new PrintCommand(jsonEditor));
        invoker.registerCommand("save", new SaveCommand(jsonEditor));
        invoker.registerCommand("saveas", new SaveAsCommand(jsonEditor));
        invoker.registerCommand("exit", new ExitCommand(jsonEditor));
        invoker.registerCommand("validate", new ValidateCommand(jsonEditor));
        invoker.registerCommand("search", new SearchCommand(jsonEditor));
        invoker.registerCommand("delete", new DeleteCommand(jsonEditor));
        invoker.registerCommand("contains", new ContainsCommand(jsonEditor));
        invoker.registerCommand("set", new SetCommand(jsonEditor));
        invoker.registerCommand("create", new CreateCommand(jsonEditor));
        invoker.registerCommand("move", new MoveCommand(jsonEditor));
    }
    catch (const std::invalid_argument&)
    {
        ConsoleLogger::logCritical("Couldn't setup all commands properly. \nPlease restart the app.");
    } 
}

void AppController::run() {
    std::string commandLine;

    for(;;){
        ConsoleLogger::logInfo("Enter a command:");
        std::getline(std::cin, commandLine);
        processCommand(commandLine);
    }
}

void AppController::processCommand(const std::string& commandLine) {
    try
    {
        invoker.executeCommand(commandLine);
    }
    catch (const std::exception& e)
    {
        ConsoleLogger::logInfo(e.what());
    }
}
