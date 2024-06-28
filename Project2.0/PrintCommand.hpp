#ifndef PRINT_COMMAND_HPP
#define PRINT_COMMAND_HPP

#include <string>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class PrintCommand : public Command {
public:
    PrintCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string json;
};

#endif // PRINT_COMMAND_HPP
