#ifndef OPENCOMMAND_HPP
#define OPENCOMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class OpenCommand : public Command {
private:
    Receiver& receiver;
    std::string filePath;

public:
    OpenCommand(const std::string& name, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;
};

#endif // OPENCOMMAND_HPP
