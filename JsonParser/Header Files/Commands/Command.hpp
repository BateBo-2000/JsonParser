#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <string>

class Command {
public:
    Command(){}
    virtual ~Command() = default;
    virtual void setArguments(const std::vector<std::string>& args) = 0;
    virtual void execute() = 0;
};

#endif // COMMAND_HPP
