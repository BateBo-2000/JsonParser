#ifndef EXIT_COMMAND_HPP
#define EXIT_COMMAND_HPP

#include <string>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class ExitCommand : public Command {
public:
    ExitCommand(const std::string& name, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;
private: 
    Receiver& receiver;
    bool forseExit;
};

#endif // EXIT_COMMAND_HPP
