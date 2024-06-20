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
        if (!filePath.empty() && !jsonContent.empty())  std::cerr << "Still working with file: " << filePath << std::endl;
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
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
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
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    //parse the JSON string
    JsonParser parser(jsonContent);
    Jvalue* root = parser.parse();

    // Search for the key and collect results
    std::vector<Jvalue*> jValues;
    searchJsonKey(root, key, jValues);

    //convert from objects to string
    formatSearchResult(searchResult, jValues);

    //clean up
    delete root;
}

void Receiver::containsValue(const std::string& searchValue, std::string& searchResult) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");

    //parse the JSON string
    JsonParser parser(jsonContent);
    Jvalue* root = parser.parse();

    //search for the value and collect results
    std::vector<Jvalue*> jValues;
    searchJsonValue(root, searchValue, jValues);
    
    //convert from objects to string
    formatSearchResult(searchResult, jValues);

    //clean up
    delete root;
}

void Receiver::deleteJsonValue(const std::string& path) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
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

    //prettify
    jsonContent = Utility::prettifyJson(jsonContent);

    //clean up
    delete root;
}

void Receiver::setJsonValue(const std::string& path, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    //parse the JSON string
    JsonParser parser(jsonContent);
    Jvalue* root = parser.parse();

    //split the path arguments
    std::vector<std::string> pathArgs;
    splitPathArgs(path, pathArgs);
    if (pathArgs.empty()) throw std::runtime_error("Invalid path.");
        
    //followThePath
    Jvalue* target = followPath(root, pathArgs);

    // Set the new value
    setValue(target, value);

    //deparse the structure to string
    jsonContent = parser.deparse(root);

    //prettify
    jsonContent = Utility::prettifyJson(jsonContent);

    //clean up
    delete root;
}

void Receiver::create(const std::string& path, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    //parse the JSON string
    JsonParser parser(jsonContent);
    Jvalue* root = parser.parse();

    std::vector<std::string> pathArgs;
    splitPathArgs(path, pathArgs);

    
    if (pathArgs.empty()) throw std::runtime_error("Invalid path.");
    std::string key = pathArgs.back();
    pathArgs.pop_back();
    Jvalue* target = followPath(root, pathArgs);

    if (target->getType() != JSONObject) {
        throw std::runtime_error("Cannot add key-value pair to a non object.");
    }

    //check if there isnt such key
    std::vector<Jvalue*> foundDuplicates;
    searchJsonKey(root, key, foundDuplicates);
    if (!foundDuplicates.empty()) {
        throw std::runtime_error("Key already exists at the specified path.");
    }
    //if all is good add it to object
    createNewPairInObject(target, key, value);
    //Works
    
    //deparse the structure to string
    jsonContent = parser.deparse(root);

    //prettify
    jsonContent = Utility::prettifyJson(jsonContent);

    //clean up
    delete root;
}

void Receiver::moveJsonValue(std::string& json, const std::string& from, const std::string& to) {

}


//internals
void Receiver::searchJsonKey(Jvalue* root, const std::string& searchKey, std::vector<Jvalue*>& jValues) {
    if (root->getType() == JSONObject) {
        JsonObject* obj = static_cast<JsonObject*>(root);
        if (obj) {
            std::vector<Jvalue*> result = obj->getByKey(searchKey);
            jValues.insert(jValues.end(), result.begin(), result.end());

            const std::vector<Jvalue*>* objValue = obj->getValue();
            for (Jvalue* value : *objValue) {
                searchJsonKey(value, searchKey, jValues);
            }
        }
    }
    else if (root->getType() == JSONArray) {
        JsonArray* arr = static_cast<JsonArray*>(root);
        if (arr) {
            const std::vector<Jvalue*>& values = arr->getValue();
            for (Jvalue* value : values) {
                searchJsonKey(value, searchKey, jValues);
            }
        }
    }
}

void Receiver::searchJsonValue(Jvalue* root, const std::string& searchValue, std::vector<Jvalue*>& jValues) {
    if (root->getType() == JSONObject) {
        JsonObject* obj = static_cast<JsonObject*>(root);
        if (obj) {
            std::vector<Jvalue*> result = obj->getByValue(searchValue);
            jValues.insert(jValues.end(), result.begin(), result.end());

            const std::vector<Jvalue*>* objValue = obj->getValue();
            for (Jvalue* value : *objValue) {
                searchJsonValue(value, searchValue, jValues);
            }
        }
    }
    else if (root->getType() == JSONArray) {
        JsonArray* arr = static_cast<JsonArray*>(root);
        if (arr) {
            const std::vector<Jvalue*>& values = arr->getValue();
            for (Jvalue* value : values) {
                searchJsonValue(value, searchValue, jValues);
            }
        }
    }
}

void Receiver::formatSearchResult(std::string& searchResult, const std::vector<Jvalue*>& jValues) {
    if (jValues.empty()) {
        //return empty array
        searchResult = "[]";
    }
    else {
        //format the found data
        searchResult += "[";
        for (size_t i = 0; i < jValues.size(); ++i) {
            searchResult += "\"" + jValues[i]->getKey() +"\" : "+ jValues[i]->toString() + ",";
        }
        searchResult.pop_back(); //remove the last comma 
        searchResult += "]";
        searchResult = Utility::prettifyJson(searchResult);
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
        Jvalue* target = obj->getByExactKey(keyOrIndexToDelete);
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

void Receiver::setValue(Jvalue* target, const std::string& value) {
    if (!target) {
        throw std::invalid_argument("Target value not found.");
    }

    switch (target->getType())
    {
    case JSONNull: {
        if (value != "null")
            throw std::invalid_argument("Cannot change the type of null.");
    }
    case JSONBool: {
        if (value != "true" && value != "false") {
            throw std::invalid_argument("Invalid boolean value: " + value);
        }
        static_cast<JsonBool*>(target)->setValue(value == "true");
        break;
    }
    case JSONNumber: {
        if (isNumber(value)) {
            try {
                double numValue = std::stod(value);
                static_cast<JsonNumber*>(target)->setValue(numValue);
            }
            catch (const std::exception&) {
                throw std::invalid_argument("Failed while coverting to number: " + value);
            }
        }
        else {
            throw std::invalid_argument("Invalid number value: " + value);
        }
        
        break;
    }
    case JSONString: {
        static_cast<JsonString*>(target)->setValue(value);
        break;
    }
    case JSONArray: {
        throw std::invalid_argument("Cannot set the value of array to a primitive type.");
    }
    case JSONObject: {
        throw std::invalid_argument("Cannot set the value of object to a primitive type.");
    }
    default:
        throw std::runtime_error("Unsupported value type for set operation.");
    }
}

bool Receiver::isNumber(const std::string& str) {
    bool foundDot = false;
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == '.' && !foundDot) {
            continue;
        }
        else if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

void Receiver::createNewPairInObject(Jvalue* target, const std::string& key, const std::string& value) {
    if (target->getType() == JSONObject) {
        JsonObject* obj = static_cast<JsonObject*>(target);
        if (!obj) throw std::runtime_error("Failed to cast to JsonObject.");

        Jvalue* pair = nullptr;
        if (value == "null") {
            pair = new(std::nothrow) JsonNull(key);
        }
        else if (value == "true" || value == "false") {
            pair = new(std::nothrow) JsonBool(key, value == "true");
        }
        else if (isNumber(value)){
            double number = std::stod(value);
            pair = new(std::nothrow) JsonNumber(key, number);
        }
        else {
            pair = new(std::nothrow) JsonString(key, value);
        }
        if (obj == nullptr) throw std::runtime_error("Something went wrong while creating the key-value pair.\n Please try again.");
        obj->add(pair);
    }  
}

void Receiver::addToArray(Jvalue* target, const std::string& value) {
    if (target->getType() == JSONArray) {
        JsonArray* array = static_cast<JsonArray*>(target);
        if (!array) throw std::runtime_error("Failed to cast to JsonObject.");

        Jvalue* pair = nullptr;
        if (array->getArrayType() == JSONNull) {
            pair = new(std::nothrow) JsonNull("");
        }
        else if (array->getArrayType() == JSONBool) {
            pair = new(std::nothrow) JsonBool("", value == "true");
        }
        else if (array->getArrayType() == JSONNumber && isNumber(value)) {
            double number = std::stod(value);
            pair = new(std::nothrow) JsonNumber("", number);
        }
        else if (array->getArrayType() == JSONString) {
            pair = new(std::nothrow) JsonString("", value);
        }
        else if (array->getArrayType() == JSONArray) {
            throw std::invalid_argument("Cannot add value with type String to array with type array");
        }else{
            throw std::invalid_argument("Cannot add value with type String to array with type object");
        }
        if (pair == nullptr) throw std::runtime_error("Something went wrong while creating the value to the array.\n Please try again.");
        array->add(pair);
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
            current = obj->getByExactKey(pathArs[i]);
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