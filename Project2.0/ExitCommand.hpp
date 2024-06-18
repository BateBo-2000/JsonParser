// ExitCommand.hpp
#ifndef EXIT_COMMAND_HPP
#define EXIT_COMMAND_HPP

#include "Command.hpp"
#include "Receiver.hpp"

class ExitCommand : public Command {
public:
    ExitCommand(const std::string& name, Receiver& receiver);
    void execute() override;
private: 
    Receiver& receiver;
};

#endif // EXIT_COMMAND_HPP
