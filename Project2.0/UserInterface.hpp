#pragma once
#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP
#include <string>
class UserInterface {
    virtual void logInfo(const std::string& message) const = 0;
    virtual void logWarning(const std::string& message) const = 0;
    virtual void logError(const std::string& message) const = 0;
    virtual void logCritical(const std::string& message) const = 0;
    virtual void logJson(const std::string& jsonContent) const = 0;
};

#endif // !USER_INTERFACE_HPP
