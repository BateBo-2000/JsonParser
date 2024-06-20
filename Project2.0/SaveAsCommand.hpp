#ifndef SAVE_AS_COMMAND_HPP
#define SAVE_AS_COMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class SaveAsCommand : public Command {
public:
    SaveAsCommand(const std::string& name, Receiver& receiver);
    void setArguemnts(const std::vector<std::string>& args) override;
    virtual void execute() override;

private:
    Receiver& receiver;
    std::string newFilePath;
    //helper function
    void changeName(std::string& path, const std::string& newName);
};

#endif // SAVE_AS_COMMAND_HPP
