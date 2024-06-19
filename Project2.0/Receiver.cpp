#include "Receiver.hpp"
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
    try {
        JsonParser parser(jsonContent);
        Jvalue* root = parser.parse();
        delete root;
        return true;
    }
    catch (const std::exception&) {
        return false;
    }
}



void Receiver::setJsonValue(const std::string& path, const std::string& key) {

}

void Receiver::deleteJsonValue(std::string& json, const std::string& path) {
   
}

void Receiver::moveJsonValue(std::string& json, const std::string& from, const std::string& to) {

}

void Receiver::createJsonValue(std::string& json, const std::string& path, const std::string& value) {
   
}

void searchForKey(Jvalue* value, const std::string& key, std::vector<Jvalue*>& results) {
    switch (value->getType()) {
    case JSONObject: {
        JsonObject* obj = dynamic_cast<JsonObject*>(value);
        if (!obj) {
            throw std::runtime_error("Failed to cast to JsonObject");
        }
        Jvalue* result = obj->getByKey(key);
        if (result) {
            results.push_back(result);
        }

        const std::vector<Jvalue*>* objValue = obj->getValue();
        for (size_t i = 0; i < objValue->size(); i++) {
            searchForKey((*objValue)[i], key, results);
        }
        break;
    }
    case JSONArray: {
        JsonArray* arr = dynamic_cast<JsonArray*>(value);
        if (!arr) {
            throw std::runtime_error("Failed to cast to JsonArray");
        }

        vector<Jvalue*> values = arr->getValue();
        for (Jvalue* val : values) {
            searchForKey(val, key, results);
        }
        break;
    }
    case JSONString:
    case JSONNumber:
    case JSONBool:
    case JSONNull:
        //they dont have keys
        break;
    default:
        throw std::runtime_error("Unknown JsonType encountered");
    }
}

void Receiver::searchJson(const std::string& key, std::vector<std::string>& searchResult) {
        //parse the JSON string
        JsonParser parser(jsonContent);
        Jvalue* root = parser.parse();
        
        // Search for the key and collect results
        std::vector<Jvalue*> jValues;
        searchForKey(root, key, jValues);

        // Convert found values to string and store in results
        for (Jvalue* value : jValues) {
            searchResult.push_back(value->toString());
        }
        //clean up
        delete root;
}

void Receiver::containsValue(const std::string& json, const std::string& value) {

}


//internals

void Receiver::splitPathArgs(const std::string& path, std::vector<std::string>& components) {
    size_t pos = 0;
    size_t start = 0;

    while (pos < path.size()) {
        if (path[pos] == '.' || path[pos] == '[' || path[pos] == ']') {
            if (pos > start) {
                components.push_back(path.substr(start, pos - start));
            }
            components.push_back(std::string(1, path[pos]));
            start = pos + 1;
        }
        ++pos;
    }

    if (pos > start) {
        components.push_back(path.substr(start, pos - start));
    }

    return;
}

Jvalue* Receiver::followPath(Jvalue* root, const std::string& path) {

    std::vector<std::string> pathArs;
    splitPathArgs(path, pathArs);
    Jvalue* current = root;

    for (int i = 0; i < pathArs.size(); i++) {
        if (current->getType() == JSONObject) {
            JsonObject* obj = static_cast<JsonObject*>(current);
            current = obj->getByKey(pathArs[i]);
            if (!current) {
                throw std::runtime_error("Path not found in JSON object: " + pathArs[i]);
            }
        }
        else if (current->getType() == JSONArray) {
            JsonArray* arr = static_cast<JsonArray*>(current);
            size_t index = std::stoi(pathArs[i]);
            if (index >= arr->getValue().size()) {
                throw std::out_of_range("Index out of range in JSON array: " + pathArs[i]);
            }
            current = (*arr)[index];
        }
        else {
            throw std::runtime_error("Invalid path: path argument " + pathArs[i] + " is not an object or array.");
        }
    }

    return current;
}