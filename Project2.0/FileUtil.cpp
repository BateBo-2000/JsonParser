#include "FileUtil.hpp"
#include "Logger.hpp"

void FileUtil::getInputFileLocation(std::string& path) {
    Logger::getLogger().logInfo("Enter the file location:");
    std::getline(std::cin, path);
    std::ifstream file(path);
    // Validate the path
    if (!file.good()) {
        throw std::runtime_error("File not found or cannot be opened: " + path);
    }
}

void FileUtil::getOutputFileLocation(std::string& path) {
    Logger::getLogger().logInfo("Enter output file location: ");
    std::getline(std::cin, path);
    std::ofstream file(path);
    // Validate the path
    if (!file.good()) {
        throw std::runtime_error("Invalid output file location: " + path);
    }
}

