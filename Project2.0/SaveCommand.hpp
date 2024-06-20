#ifndef SAVE_COMMAND_HPP
#define SAVE_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"
class SaveCommand : public Command {
public:
    SaveCommand(const std::string& name, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string filePath;
};

#endif // SAVE_COMMAND_HPP
