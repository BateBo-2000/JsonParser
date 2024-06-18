#include "ApplicationController.hpp"
#include "OpenCommand.hpp"
#include "PrintCommand.hpp"

AppController::AppController() {
    // Register commands with the Invoker
    invoker.registerCommand(new OpenCommand("open",jsonEditor));
    invoker.registerCommand(new PrintCommand("print", jsonEditor));
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
    invoker.executeCommand(commandLine);
}
