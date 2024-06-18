#include "ApplicationController.hpp"
#include "OpenCommand.hpp"
#include "PrintCommand.hpp"
#include "SaveCommand.hpp"
#include "SaveAsCommand.hpp"
#include "ExitCommand.hpp"
#include "ValidateCommand.hpp"

AppController::AppController() {
    // Register commands with the Invoker
    invoker.registerCommand(new OpenCommand("open",jsonEditor));
    invoker.registerCommand(new PrintCommand("print", jsonEditor));
    invoker.registerCommand(new SaveCommand("save", jsonEditor));
    invoker.registerCommand(new SaveAsCommand("saveas", jsonEditor));
    invoker.registerCommand(new ExitCommand("exit", jsonEditor));
    invoker.registerCommand(new ValidateCommand("validate", jsonEditor));
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
