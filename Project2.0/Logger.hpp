#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "UserInterface.hpp"

#include <iostream>
#include <string>

class ConsoleLogger: public UserInterface {
public:
    void logInfo(const std::string& message) const override;
    void logWarning(const std::string& message) const override;
    void logError(const std::string& message) const override;
    void logCritical(const std::string& message) const override;
    void logJson(const std::string& jsonContent) const override;

private:
    void log(const std::string& message, const std::string& level) const;
};

#endif // !LOGGER_HPP

