#include "..\\Header Files\\ApplicationController.hpp"
#include "..\\Header Files\\Commands\\OpenCommand.hpp"
#include "..\\Header Files\\Commands\\PrintCommand.hpp"
#include "..\\Header Files\\Commands\\SaveCommand.hpp"
#include "..\\Header Files\\Commands\\SaveAsCommand.hpp"
#include "..\\Header Files\\Commands\\ExitCommand.hpp"
#include "..\\Header Files\\Commands\\ValidateCommand.hpp"
#include "..\\Header Files\\Commands\\SearchCommand.hpp"
#include "..\\Header Files\\Commands\\DeleteCommand.hpp"
#include "..\\Header Files\\Commands\\ContainsCommand.hpp"
#include "..\\Header Files\\Commands\\SetCommand.hpp"
#include "..\\Header Files\\Commands\\CreateCommand.hpp"
#include "..\\Header Files\\Commands\\MoveCommand.hpp"
#include "..\\Header Files\\Commands\\HelpCommand.hpp"

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
        invoker.registerCommand("help", new HelpCommand(consoleLogger));
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
    catch (const CommandException& e)
    {
        consoleLogger.logError("Error while executing command: " + string(e.what()));
    }
    catch (const InvokerException& e)
    {
        consoleLogger.logError(e.what());
    }
    catch (const std::exception&)
    {
        consoleLogger.logError("Something went wrong!");
    }
}
