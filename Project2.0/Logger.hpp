#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "UserInterface.hpp"

#include <iostream>
#include <string>

class ConsoleLogger: public UserInterface {
public:
    static void logInfo(const std::string& message);
    static void logWarning(const std::string& message);
    static void logError(const std::string& message);
    static void logCritical(const std::string& message);
    static void logJson(const std::string& jsonContent);

private:
    static void log(const std::string& message, const std::string& level);
};

#endif // !LOGGER_HPP

