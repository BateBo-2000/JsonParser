#ifndef VALIDATECOMMAND_HPP
#define VALIDATECOMMAND_HPP

#include <string>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class ValidateCommand : public Command {
public:
    ValidateCommand(const std::string& name, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
};

#endif // VALIDATECOMMAND_HPP