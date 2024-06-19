// DeleteCommand.hpp
#ifndef DELETE_COMMAND_HPP
#define DELETE_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class DeleteCommand : public Command {
public:
    DeleteCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string path;
};

#endif // DELETE_COMMAND_HPP
