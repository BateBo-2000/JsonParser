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
        invoker.registerCommand("open", new OpenCommand(consoleLogger ,jsonEditor)); //the opertor new returns pointer
        invoker.registerCommand("print", new PrintCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("save", new SaveCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("saveas", new SaveAsCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("exit", new ExitCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("validate", new ValidateCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("search", new SearchCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("delete", new DeleteCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("contains", new ContainsCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("set", new SetCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("create", new CreateCommand(consoleLogger, jsonEditor));
        invoker.registerCommand("move", new MoveCommand(consoleLogger, jsonEditor));
    }
    catch (const std::invalid_argument&)
    {
        consoleLogger.logCritical("Couldn't setup all commands properly. \nPlease restart the app.");
    } 
}

void AppController::run() {
    std::string commandLine;

    for(;;){
        consoleLogger.logInfo("Enter a command:");
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
        consoleLogger.logInfo(e.what());
    }
}
