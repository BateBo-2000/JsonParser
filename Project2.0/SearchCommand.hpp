#ifndef SEARCH_COMMAND_HPP
#define SEARCH_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"
class SearchCommand : public Command {
public:
    SearchCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args);
    virtual void execute() override;

private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string searchKey;
};
#endif // SEARCH_COMMAND_HPP
