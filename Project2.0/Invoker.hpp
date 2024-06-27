#pragma once
#ifndef INVOKER_HPP
#define INVOKER_HPP

#include <vector>
#include <string>
#include "Command.hpp"

class Invoker {
public:
    Invoker();
    ~Invoker();
    //todo copy const + op=
    void registerCommand(const std::string& name, Command* cmd);
    void executeCommand(const std::string& commandLine);

private:
    //holds the commands
    std::vector<Command*> commandObjects;
    std::vector<std::string> commandNames;
    //helper functions
    void splitCommandLine(const std::string& commandLine, std::vector<std::string>& args);
    size_t getArgEnd(const std::string str, size_t start);
};

#endif // INVOKER_HPP
