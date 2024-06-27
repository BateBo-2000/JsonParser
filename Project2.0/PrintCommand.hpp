#ifndef PRINT_COMMAND_HPP
#define PRINT_COMMAND_HPP

#include <string>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class PrintCommand : public Command {
public:
    PrintCommand(Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;

private:
    Receiver& receiver;
    std::string json;
};

#endif // PRINT_COMMAND_HPP
