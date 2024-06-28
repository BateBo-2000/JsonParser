#ifndef MOVE_COMMAND_HPP
#define MOVE_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class MoveCommand : public Command {
public:
    MoveCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string from;
    std::string to;
};

#endif // MOVE_COMMAND_HPP
