// SetCommand.hpp
#ifndef SET_COMMAND_HPP
#define SET_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class SetCommand : public Command {
public:
    SetCommand(const std::string& name, Receiver& receiver);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string path;
    std::string value;
};

#endif // SET_COMMAND_HPP
