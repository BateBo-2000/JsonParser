#ifndef CONTAINS_COMMAND_HPP
#define CONTAINS_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class ContainsCommand : public Command {
public:
    ContainsCommand(Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string searchValue;
};

#endif // CONTAINS_COMMAND_HPP
