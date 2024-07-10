#ifndef CONTAINS_COMMAND_HPP
#define CONTAINS_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "../../Header Files/Receiver.hpp"
#include "Command.hpp"
#include "../../Header Files/Logger.hpp"

class ContainsCommand : public Command {
public:
    ContainsCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string searchValue;
};

#endif // CONTAINS_COMMAND_HPP
