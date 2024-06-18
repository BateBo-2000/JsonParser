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

void Receiver::setJsonValue(std::string& json, const std::string& path, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    size_t pos = 0;
    while ((pos = json.find(path, pos)) != std::string::npos) {
        size_t startQuote = json.rfind('\"', pos);
        if (startQuote == std::string::npos) {
            pos += path.length();
            continue;
        }

        size_t endQuote = json.find('\"', startQuote + 1);
        if (endQuote == std::string::npos) {
            pos += path.length();
            continue;
        }

        std::string quotedPath = json.substr(startQuote, endQuote - startQuote + 1);
        if (quotedPath.find(path) != std::string::npos) {
            size_t colonPos = json.find(':', endQuote);
            if (colonPos == std::string::npos) {
                throw std::runtime_error("Failed to set value: Invalid path");
            }

            // Determine if the value is quoted or not
            size_t startValue = json.find_first_not_of(" \n\t\r", colonPos + 1);
            if (json[startValue] == '\"') {
                size_t endValue = json.find_last_of('\"');
                json.replace(startValue, endValue - startValue + 1, value);
            }
            else {
                size_t endValue = json.find_first_of(" ,}\n\t\r", startValue);
                json.replace(startValue, endValue - startValue, value);
            }
            return;
        }
        pos = endQuote + 1;
    }

    throw std::runtime_error("Failed to set value: Path not found");
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

void Receiver::deleteJsonValue(std::string& json, const std::string& path) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");

    size_t pos = 0;
    while ((pos = json.find(path, pos)) != std::string::npos) {
        size_t startQuote = json.rfind('\"', pos);
        if (startQuote == std::string::npos) {
            pos += path.length();
            continue;
        }

        size_t endQuote = json.find('\"', startQuote + 1);
        if (endQuote == std::string::npos) {
            pos += path.length();
            continue;
        }

        std::string quotedPath = json.substr(startQuote, endQuote - startQuote + 1);
        if (quotedPath.find(path) != std::string::npos) {
            size_t colonPos = json.find(':', endQuote);
            if (colonPos == std::string::npos) {
                throw std::runtime_error("Failed to delete value: Invalid path");
            }

            size_t startValue = json.find_first_not_of(" \n\t\r", colonPos + 1);
            size_t endValue = json.find_first_of(" ,}\n\t\r", startValue);
            if (endValue == std::string::npos) {
                endValue = json.length();
            }

            // Remove key-value pair
            json.erase(startQuote, endValue - startQuote);
            return;
        }
        pos = endQuote + 1;
    }

    throw std::runtime_error("Failed to delete value: Path not found");
}

void Receiver::moveJsonValue(std::string& json, const std::string& from, const std::string& to) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    std::string value;
    try {
        value = getJsonValue(json, from);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to move value: " + std::string(e.what()));
    }

    try {
        deleteJsonValue(json, from);
        setJsonValue(json, to, value);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Failed to move value: " + std::string(e.what()));
    }
}

void Receiver::createJsonValue(std::string& json, const std::string& path, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    size_t pos = 0;
    while ((pos = json.find(path, pos)) != std::string::npos) {
        size_t startQuote = json.rfind('\"', pos);
        if (startQuote == std::string::npos) {
            pos += path.length();
            continue;
        }

        size_t endQuote = json.find('\"', startQuote + 1);
        if (endQuote == std::string::npos) {
            pos += path.length();
            continue;
        }

        std::string quotedPath = json.substr(startQuote, endQuote - startQuote + 1);
        if (quotedPath.find(path) != std::string::npos) {
            size_t colonPos = json.find(':', endQuote);
            if (colonPos == std::string::npos) {
                throw std::runtime_error("Failed to create value: Invalid path");
            }

            size_t startValue = json.find_first_not_of(" \n\t\r", colonPos + 1);
            size_t endValue = json.find_first_of(" ,}\n\t\r", startValue);
            if (endValue == std::string::npos) {
                endValue = json.length();
            }

            // Insert new key-value pair
            json.insert(endValue, ", \"" + value + "\"");
            return;
        }
        pos = endQuote + 1;
    }

    throw std::runtime_error("Failed to create value: Path not found");
}




//To do:
void Receiver::searchJson(const std::string& json, const std::string& key) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    std::vector<std::string> results;
    size_t pos = 0;

    while ((pos = json.find(key, pos)) != std::string::npos) {
        size_t startQuote = json.rfind('\"', pos);
        if (startQuote == std::string::npos) {
            break;  // invalid JSON
        }

        size_t endQuote = json.find('\"', startQuote + 1);
        if (endQuote == std::string::npos) {
            break;  // invalid JSON
        }

        size_t colonPos = json.find(':', endQuote);
        if (colonPos == std::string::npos || colonPos > pos) {
            pos = endQuote + 1;
            continue;
        }

        size_t valueStart = json.find_first_not_of(' ', colonPos + 1);
        if (valueStart == std::string::npos) {
            break;  // invalid JSON
        }

        size_t valueEnd = json.find_first_of(",}", valueStart);
        if (valueEnd == std::string::npos) {
            throw std::runtime_error("Invalid JSON format.");
        }

        std::string value = trim(json.substr(valueStart, valueEnd - valueStart));
        results.push_back(value);

        // Move to the next position to continue searching
        pos = valueEnd + 1;
    }

    if (results.empty()) {
        std::cout << "Key not found: " << key << std::endl;
    }
    else {
        std::cout << "Found key '" << key << "' with values:" << std::endl;
        for (const auto& value : results) {
            std::cout << value << std::endl;
        }
    }
}

void Receiver::containsValue(const std::string& json, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    std::vector<std::string> results;

    size_t pos = 0;
    while ((pos = json.find(value, pos)) != std::string::npos) {
        // Check if the value is quoted
        size_t startQuote = json.rfind('\"', pos);
        if (startQuote == std::string::npos) {
            pos += value.length();
            continue;
        }

        size_t endQuote = json.find('\"', startQuote + 1);
        if (endQuote == std::string::npos) {
            pos += value.length();
            continue;
        }

        // Extract the quoted value
        std::string quotedValue = json.substr(startQuote, endQuote - startQuote + 1);
        if (quotedValue.find(value) != std::string::npos) {
            results.push_back(trim(quotedValue));
        }

        // Move to the next position to continue searching
        pos = endQuote + 1;
    }

    if (results.empty()) {
        std::cout << "No value containing '" << value << "' found in the JSON." << std::endl;
    }
    else {
        std::cout << "Found values containing '" << value << "' in the JSON:" << std::endl;
        for (const auto& val : results) {
            std::cout << val << std::endl;
        }
    }
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