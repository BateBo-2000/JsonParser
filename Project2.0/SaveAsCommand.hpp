// SaveAsCommand.hpp
#ifndef SAVE_AS_COMMAND_HPP
#define SAVE_AS_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class SaveAsCommand : public Command {
public:
    SaveAsCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string newFilePath;
};

#endif // SAVE_AS_COMMAND_HPP
