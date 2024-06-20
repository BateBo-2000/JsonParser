// CreateCommand.hpp
#ifndef CREATE_COMMAND_HPP
#define CREATE_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class CreateCommand : public Command {
public:
    CreateCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string path;
    std::string value;
};

#endif // CREATE_COMMAND_HPP
