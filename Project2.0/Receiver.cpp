#include "Receiver.hpp"
#include "FileReader.hpp"
#include "FileWriter.hpp"

/*
    To do: do it with logger
*/


Receiver::Receiver() {}

void Receiver::readFile(const std::string& filePath) {
    FileReader fileReader;
    try {
        fileReader.readFile(filePath, jsonContent);
        //auto saving the location
        currentFileLocation = filePath;
        std::cout << "File opened successfully: " << filePath << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error opening file: " << e.what() << std::endl;
    }
}

void Receiver::writeFile(const std::string& newFilePath) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    FileWriter fileWriter;
    try {
        fileWriter.writeFile(newFilePath, jsonContent);
        std::cout << "JSON saved to file: " << newFilePath << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving JSON to file: " << e.what() << std::endl;
    }
}

std::string Receiver::getFileLocation() const {
    return currentFileLocation;
}

void Receiver::printJson() const {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    std::cout << jsonContent << std::endl;
}

bool Receiver::isValidJson() const {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");

    int braceCount = 0;
    bool inString = false;
    bool escape = false;

    for (size_t i = 0; i < jsonContent.size(); ++i) {
        char current = jsonContent[i];

        if (escape) {
            escape = false;
            continue;
        }

        if (current == '\\') {
            escape = true;
            continue;
        }

        if (current == '"') {
            inString = !inString;
            continue;
        }

        if (inString) {
            continue;
        }

        if (current == '{') {
            braceCount++;
        }
        else if (current == '}') {
            braceCount--;
            if (braceCount < 0) {
                return false;
            }
        }
    }

    return braceCount == 0 && !inString;
}



void Receiver::setJsonValue(std::string& json, const std::string& path, const std::string& value) {
    
}

void Receiver::deleteJsonValue(std::string& json, const std::string& path) {
   
}

void Receiver::moveJsonValue(std::string& json, const std::string& from, const std::string& to) {

}

void Receiver::createJsonValue(std::string& json, const std::string& path, const std::string& value) {
   
}

void Receiver::searchJson(const std::string& json, const std::string& key) {

}

void Receiver::containsValue(const std::string& json, const std::string& value) {

}

void Receiver::followPathToDir(std::vector<std::string>& path, size_t& dirStart, size_t& dirEnd) {

}



//internals

std::string Receiver::getJsonValue(const std::string& json, const std::string& path) {
    // Implement JSON value retrieval logic
    // Example: Assume simple path lookup and return value
    std::size_t pos = json.find(path);
    if (pos != std::string::npos) {
        std::size_t valueStart = json.find(':', pos);
        if (valueStart != std::string::npos) {
            std::size_t valueEnd = json.find(',', valueStart);
            if (valueEnd == std::string::npos) {
                valueEnd = json.find('}', valueStart);
            }
            return json.substr(valueStart + 1, valueEnd - valueStart - 1);
        }
    }
    return ""; // Return empty string if value not found or error occurs
}

std::string Receiver::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

