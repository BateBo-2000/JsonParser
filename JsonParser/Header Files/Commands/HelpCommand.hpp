#ifndef HELP_COMMAND_HPP
#define HELP_COMMAND_HPP

#include <string>
#include "Command.hpp"
#include "../../Header Files/Logger.hpp"
#include "../../Source Files/HelpGuide.cpp";

class HelpCommand : public Command {
public:
    HelpCommand(ConsoleLogger& console);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;
private:
    ConsoleLogger& console;
};

#endif // HELP_COMMAND_HPP