#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include <string>

class Command {
public:
    Command(const std::string& name): name(name){}
    virtual ~Command() = default;
    virtual void setArguemnts(const std::vector<std::string>& args) = 0;
    virtual void execute() = 0;
    std::string& getName() {
        return name;
    }
protected:
    std::string name;
};

#endif // COMMAND_HPP
