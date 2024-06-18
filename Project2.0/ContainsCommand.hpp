// ContainsCommand.hpp
#ifndef CONTAINS_COMMAND_HPP
#define CONTAINS_COMMAND_HPP
#include <string>
#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class ContainsCommand : public Command {
public:
    ContainsCommand(const std::string& name, Receiver& receiver);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string json;
    std::string value;
};

#endif // CONTAINS_COMMAND_HPP
