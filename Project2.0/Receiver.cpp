#include "Receiver.hpp"
/*
    To do: do it with logger
*/


Receiver::Receiver() {}

void Receiver::loadFile(const std::string& filePath) {
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

bool Receiver::isValidJson(std::string* errorMsg) const { //to make it optional to get the error
    try {
        JsonParser parser(jsonContent);
        Jvalue* root = parser.parse();
        delete root;
        return true;
    }
    catch (const std::exception& e) {
        if (errorMsg) {
            *errorMsg = e.what();
        }
        return false;
    }
}

void Receiver::searchJson(const std::string& key, std::string& searchResult) {
    //parse the JSON string
    JsonParser parser(jsonContent);
    Jvalue* root = parser.parse();

    // Search for the key and collect results
    std::vector<Jvalue*> jValues;
    searchForKey(root, key, jValues);

    // Convert found values to string and store in results
    for (Jvalue* value : jValues) {
        searchResult += value->toString();
    }
    searchResult = parser.prettify(searchResult);
    //clean up
    delete root;
}

void Receiver::deleteJsonValue(const std::string& path) {
    //parse the JSON string
    JsonParser parser(jsonContent);
    Jvalue* root = parser.parse();

    //split the path arguments
    std::vector<std::string> pathArgs;
    splitPathArgs(path, pathArgs);
    if (pathArgs.empty()) {
        throw std::runtime_error("Invalid path.");
    }
    //separate the target and parent
    std::string target = pathArgs.back();
    pathArgs.pop_back();

    //follow the path to the parent
    Jvalue* parent = followPath(root, pathArgs);

    //delete the key/value pair
    deleteJsonPairAtTarget(parent, target);

    //deparse the structure to string
    jsonContent = parser.deparse(root);

    //clean up
    delete root;
}

void Receiver::setJsonValue(const std::string& path, const std::string& key) {

}

void Receiver::moveJsonValue(std::string& json, const std::string& from, const std::string& to) {

}

void Receiver::createJsonValue(std::string& json, const std::string& path, const std::string& value) {
   
}

void Receiver::containsValue(const std::string& json, const std::string& value) {

}

//internals

void Receiver::searchForKey(Jvalue* value, const std::string& key, std::vector<Jvalue*>& results) {
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

void Receiver::deleteJsonPairAtTarget(Jvalue* parent, const std::string& path) {
    std::vector<std::string> pathArgs;
    splitPathArgs(path, pathArgs);
    if (pathArgs.empty()) {
        throw std::runtime_error("Invalid path");
    }

    std::string keyOrIndexToDelete = pathArgs.back();

    // Delete the key/value pair or array element
    if (parent->getType() == JSONObject) {
        JsonObject* obj = static_cast<JsonObject*>(parent);
        Jvalue* target = obj->getByKey(keyOrIndexToDelete);
        if (target) {
            obj->removeByKey(keyOrIndexToDelete); // Remove the element from the container
            delete target; // Delete the element to free memory
        }
        else {
            throw std::runtime_error("Key not found: cannot delete element.");
        }
    }
    else if (parent->getType() == JSONArray) {
        JsonArray* arr = static_cast<JsonArray*>(parent);
        size_t indexToDelete = std::stoi(keyOrIndexToDelete);
        if (indexToDelete < arr->getValue().size()) {
            Jvalue* target = arr->getValue()[indexToDelete];
            arr->removeByIndex(indexToDelete); // Remove the element from the container
            delete target; // Delete the element to free memory
        }
        else {
            throw std::runtime_error("Index out of range: cannot delete element");
        }
    }
    else {
        throw std::runtime_error("Invalid path or unsupported JSON type at path");
    }
}

void Receiver::splitPathArgs(const std::string& path, std::vector<std::string>& components) {
    size_t pos = 0;
    size_t start = 0;

    while (pos < path.size()) {
        if (path[pos] == '.' || path[pos] == '[' || path[pos] == ']') {
            if (pos > start) {
                components.push_back(path.substr(start, pos - start));
            }
            if (path[pos] == '[' || path[pos] == ']' || path[pos] == '.') {
                // Skip these characters
                start = pos + 1;
            }
            else {
                components.push_back(std::string(1, path[pos]));
                start = pos + 1;
            }
        }
        ++pos;
    }

    if (pos > start) {
        components.push_back(path.substr(start, pos - start));
    }
    return;
}

Jvalue* Receiver::followPath(Jvalue* root, std::vector<std::string> pathArs) {
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