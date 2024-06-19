#pragma once
#ifndef LOGGER_HDD
#define LOGGER_HDD

#include <iostream>
#include <string>

class Logger {
public:
    static void logInfo(const std::string& message);
    static void logWarning(const std::string& message);
    static void logError(const std::string& message);
    static void logCritical(const std::string& message);

private:
    void log(const std::string& message, const std::string& level);
};

#endif // !LOGGER_HDD

