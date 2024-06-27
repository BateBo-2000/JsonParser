#ifndef CREATE_COMMAND_HPP
#define CREATE_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class CreateCommand : public Command {
public:
    CreateCommand(Receiver& receiver);
    void setArguments(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string path;
    std::string value;
};

#endif // CREATE_COMMAND_HPP
