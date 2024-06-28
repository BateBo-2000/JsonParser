#include "Logger.hpp"

void ConsoleLogger::log(const std::string& message, const std::string& level) const {
    std::cout << "[" << level << "] " << message << std::endl;
}

void ConsoleLogger::logInfo(const std::string& message) const {
    log(message, "INFO");
}

void ConsoleLogger::logWarning(const std::string& message) const {
    log(message, "WARNING");
}

void ConsoleLogger::logError(const std::string& message) const {
    log(message, "ERROR");
}

void ConsoleLogger::logCritical(const std::string& message) const {
    log(message, "CRITICAL");
}
void ConsoleLogger::logJson(const std::string& jsonContent) const {
    log("\n" + jsonContent, "PRINT");
}

