#ifndef EXIT_COMMAND_HPP
#define EXIT_COMMAND_HPP

#include <string>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class ExitCommand : public Command {
public:
    ExitCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;
private: 
    Receiver& receiver;
    ConsoleLogger& console;
    bool forseExit;
};

#endif // EXIT_COMMAND_HPP
