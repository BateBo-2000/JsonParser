#pragma once
#ifndef APP_CONTROLLER_HPP
#define APP_CONTROLLER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Invoker.hpp"
#include "Receiver.hpp"

class AppController {
public:
    AppController();

    void run();

private:
    Invoker invoker;
    Receiver jsonEditor;

    void processCommand(const std::string& commandLine);
};

#endif // APP_CONTROLLER_HPP
