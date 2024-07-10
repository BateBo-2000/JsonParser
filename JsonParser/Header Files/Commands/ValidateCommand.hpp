#ifndef VALIDATECOMMAND_HPP
#define VALIDATECOMMAND_HPP

#include <string>
#include "../../Header Files/Receiver.hpp"
#include "Command.hpp"
#include "../../Header Files/Logger.hpp"

class ValidateCommand : public Command {
public:
    ValidateCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
};

#endif // VALIDATECOMMAND_HPP