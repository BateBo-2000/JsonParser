#include "../Header Files/Logger.hpp"

enum ConsoleLogger::LogColor {
	Default,
	LightYellow,
	Orange,
	Red,
	DarkRed,
	LightBlue,
	LightGreen
};

void ConsoleLogger::log(const std::string& message, const std::string& level, LogColor color) const {
    std::cout << consoleColorMap(color) << "[" << level << "] " << message << consoleColorMap(Default) << std::endl;
}

void ConsoleLogger::logInfo(const std::string& message) const {
    log(message, "INFO", LightBlue);
}

void ConsoleLogger::logWarning(const std::string& message) const {
    log(message, "WARNING", Orange);
}

void ConsoleLogger::logError(const std::string& message) const {
    log(message, "ERROR", Red);
}

void ConsoleLogger::logCritical(const std::string& message) const {
    log(message, "CRITICAL", DarkRed);
}
void ConsoleLogger::logJson(const std::string& jsonContent) const {
    log("\n" + jsonContent, "PRINT", LightGreen);
}

std::string ConsoleLogger::consoleColorMap(LogColor color) const{
	switch (color) {
	case LogColor::Orange: return "\033[38;5;214m";
	case LogColor::Red: return "\033[38;5;203m";
	case LogColor::DarkRed: return "\033[91m";
	case LogColor::LightBlue: return "\033[38;5;81m";	//more vibrant \033[38;5;87m
	case LogColor::LightGreen: return "\033[38;5;77m";	//more vibrant \033[38;5;40m
	default: return "\033[0m";  // Default color
	}
}
