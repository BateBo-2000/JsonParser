#pragma once
#ifndef SAVE_COMMAND_HPP
#define SAVE_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class SaveCommand : public Command {
public:
    SaveCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string filePath;
};

#endif // SAVE_COMMAND_HPP
