// SearchCommand.hpp
#ifndef SEARCH_COMMAND_HPP
#define SEARCH_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class SearchCommand : public Command {
public:
    SearchCommand(const std::string& name, Receiver& receiver);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string json;
    std::string key;
};
#endif // SEARCH_COMMAND_HPP
