// PrintCommand.hpp
#ifndef PRINT_COMMAND_HPP
#define PRINT_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class PrintCommand : public Command {
public:
    PrintCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args) override;
    void execute() override;

private:
    Receiver& receiver;
    std::string json;
};

#endif // PRINT_COMMAND_HPP
