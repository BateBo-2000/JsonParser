#include "Logger.hpp"

void Logger::log(const std::string& message, const std::string& level) {
    std::cout << "[" << level << "] " << message << std::endl;
}

void Logger::logInfo(const std::string& message) {
    log(message, "INFO");
}

void Logger::logWarning(const std::string& message) {
    log(message, "WARNING");
}

void Logger::logError(const std::string& message) {
    log(message, "ERROR");
}

void Logger::logCritical(const std::string& message) {
    log(message, "CRITICAL");
}
void Logger::logJson(const std::string& jsonContent) {
    log("\n" + jsonContent, "PRINT");
}

