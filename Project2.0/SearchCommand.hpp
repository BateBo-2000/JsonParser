// SearchCommand.hpp
#ifndef SEARCH_COMMAND_HPP
#define SEARCH_COMMAND_HPP

#include "Receiver.hpp"
#include "Command.hpp"
#include <iostream>

class SearchCommand : public Command {
public:
    SearchCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string searchKey;
};
#endif // SEARCH_COMMAND_HPP
