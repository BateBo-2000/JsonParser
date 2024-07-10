#ifndef CREATE_COMMAND_HPP
#define CREATE_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "../../Header Files/Receiver.hpp"
#include "Command.hpp"
#include "../../Header Files/Logger.hpp"

class CreateCommand : public Command {
public:
    CreateCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string path;
    std::string value;
};

#endif // CREATE_COMMAND_HPP
