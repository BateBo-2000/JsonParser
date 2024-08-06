#ifndef SET_COMMAND_HPP
#define SET_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "../../Header Files/Receiver.hpp"
#include "Command.hpp"
#include "../../Header Files/Logger.hpp"
#include "../../Header Files/Exceptions.hpp"

class SetCommand : public Command {
public:
    SetCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string path;
    std::string value;
};

#endif // SET_COMMAND_HPP
