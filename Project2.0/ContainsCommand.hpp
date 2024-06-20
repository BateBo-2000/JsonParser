#ifndef CONTAINS_COMMAND_HPP
#define CONTAINS_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class ContainsCommand : public Command {
public:
    ContainsCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string searchValue;
};

#endif // CONTAINS_COMMAND_HPP
