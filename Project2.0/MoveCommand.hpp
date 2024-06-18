// MoveCommand.hpp
#ifndef MOVE_COMMAND_HPP
#define MOVE_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class MoveCommand : public Command {
public:
    MoveCommand(const std::string& name, Receiver& receiver);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string from;
    std::string to;
};

#endif // MOVE_COMMAND_HPP
