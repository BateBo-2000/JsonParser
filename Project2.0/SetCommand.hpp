#ifndef SET_COMMAND_HPP
#define SET_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"
class SetCommand : public Command {
public:
    SetCommand(Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string path;
    std::string value;
};

#endif // SET_COMMAND_HPP
