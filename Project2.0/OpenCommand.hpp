#ifndef OPENCOMMAND_HPP
#define OPENCOMMAND_HPP

#include <string>
#include <stdexcept>
#include "Receiver.hpp"
#include "Command.hpp"
#include "Logger.hpp"

class OpenCommand : public Command {
public:
    OpenCommand(ConsoleLogger& console, Receiver& receiver);
    void setArguments(const std::vector<std::string>& args) override;
    void execute() override;
private:
    Receiver& receiver;
    ConsoleLogger& console;
    std::string filePath;
    bool dontSave;
};


#endif // OPENCOMMAND_HPP
