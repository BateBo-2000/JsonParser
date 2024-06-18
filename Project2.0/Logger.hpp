#pragma once
#ifndef LOGGER_HDD
#define LOGGER_HDD

#include <iostream>
#include <string>

class Logger {
public:
    //Making it singleton.
    static Logger& getLogger()
    {
        static Logger logger;
        return logger;
    }

    void logInfo(const std::string& message);
    void logWarning(const std::string& message);
    void logError(const std::string& message);
    void logCritical(const std::string& message);

private:

    void log(const std::string& message, const std::string& level);

    Logger() {};
    ~Logger() {};
    Logger(Logger& l) = delete;
    void operator=(Logger& l) = delete;
};

#endif // !LOGGER_HDD

#include <iostream>

