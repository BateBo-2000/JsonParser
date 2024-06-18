#ifndef VALIDATECOMMAND_HPP
#define VALIDATECOMMAND_HPP

#include "Command.hpp"
#include "Receiver.hpp"

class ValidateCommand : public Command {
public:
    ValidateCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
};

#endif // VALIDATECOMMAND_HPP