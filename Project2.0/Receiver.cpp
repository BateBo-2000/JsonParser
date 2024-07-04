#include "Receiver.hpp"

Receiver::Receiver() : root(nullptr), hasChanges(false) {}

Receiver::~Receiver() {
    if (root!=nullptr)
    {
        delete root;
    }
}

bool Receiver::loadFile(const std::string& filePath, std::string& message) {
   
    FileReader fileReader;
    try {
        fileReader.readFile(filePath, jsonContent);
        //auto saving the location
        currentFileLocation = filePath;
        message = "File opened successfully: " + filePath;
        //clean the old data
        if (root != nullptr) {
            delete root;
            root = nullptr;
        }
        hasChanges = false;

        return true;
    }
    catch (const std::exception& e) {
        message = "Error opening file: " + std::string(e.what());
        if (!filePath.empty() && !jsonContent.empty())  message += "\nStill working with file: " + filePath;
        return false;
    }
}

bool Receiver::writeFile(const std::string& newFilePath, std::string& message) {
    if (jsonContent.empty()) {
        message = "There is no open file.";
        return false;
    }
    FileWriter fileWriter;
    try {
        JsonParser parser(jsonContent);
        jsonContent = parser.deparse(root);               //deparse
        jsonContent = Utility::prettifyJson(jsonContent); //prettify

        fileWriter.writeFile(newFilePath, jsonContent);
        message = "JSON saved to file: " + newFilePath;

        hasChanges = false;
        return true;
    }
    catch (const std::exception& e) {
        message = "Error saving JSON to file: " + std::string(e.what());
        return false;
    }
}

std::string Receiver::getFileLocation() const {
    return currentFileLocation;
}

const bool Receiver::isChanged() const {
    return hasChanges;
}

const std::string& Receiver::getJson() {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    
    if (root == nullptr) {
        return jsonContent;
    }
    else {
        //do them only here and in the writeFile methods because deparse and prettify are slow
        JsonParser parser(jsonContent);
        jsonContent = parser.deparse(root);
        jsonContent = Utility::prettifyJson(jsonContent);
        return jsonContent;
    }
}

bool Receiver::isValidJson(std::string& errorMsg) { //to make it optional to get the error
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try {
        if (root == nullptr) {
            //we dont have changes
            //just try to parse and if all is good save it
            JsonParser parser(jsonContent);
            root = parser.parse();
            errorMsg += "Data has been parsed.";
            return true;  //leave it parsed for future 
        }
        else {
            //there should be strong error checking and typization in the Jvalue classes so it should be fine if its already compiled.
            //other idea: deparse then try to parse again?
            return true;
        }
    }
    catch (const std::exception& e) {
        if (root != nullptr) {  //if not valid delete all
            delete root;
            root = nullptr;
        }
        errorMsg = e.what();
        return false;
    }
}

void Receiver::searchJson(const std::string& key, std::string& searchResult) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try
    {
        //parse the JSON string
        ensureParsed();

        // Search for the key and collect results
        std::vector<Jvalue*> jValues;
        searchJsonKey(root, key, jValues);

        //convert from objects to string
        formatSearchResult(searchResult, jValues);
    }
    catch (const std::exception&)
    {
        throw;
    }
}

void Receiver::containsValue(const std::string& searchValue, std::string& searchResult) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try
    {
        //parse the JSON string
        ensureParsed();

        //search for the value and collect results
        std::vector<Jvalue*> jValues;
        searchJsonValue(root, searchValue, jValues);

        //convert from objects to string
        formatSearchResult(searchResult, jValues);
    }
    catch (const std::exception&)
    {
        throw;
    }
}

void Receiver::deleteJsonValue(const std::string& path) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try
    {
        //parse the JSON string
        ensureParsed();

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

        hasChanges = true;
    }
    catch (const std::exception&)
    {
        throw;
    }
}

void Receiver::setJsonValue(const std::string& path, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try
    {
        //parse the JSON string
        ensureParsed();

        //split the path arguments
        std::vector<std::string> pathArgs;
        splitPathArgs(path, pathArgs);
        if (pathArgs.empty()) {
            throw std::runtime_error("Invalid path.");
        }

        //followThePath
        Jvalue* target = followPath(root, pathArgs);

        // Set the new value
        setValue(target, value);

        hasChanges = true;
    }
    catch (const std::exception&)
    {
        throw;
    }
}

void Receiver::create(const std::string& path, const std::string& value) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try
    {
        //parse the JSON string
        ensureParsed();

        std::vector<std::string> pathArgs;
        splitPathArgs(path, pathArgs);

        if (pathArgs.empty()) {
            throw std::runtime_error("Invalid path.");
        }
        std::string key = pathArgs.back();
        pathArgs.pop_back();
        Jvalue* target = followPath(root, pathArgs);

        


        if (target->getType() == JSONObject || target->getType() == JSONArray) {
            //check if there isnt such key
            std::vector<Jvalue*> foundDuplicates;
            searchJsonKey(target, key, foundDuplicates);
            if (!foundDuplicates.empty()) {
                //search for array
                pathArgs.push_back(key); //adding the key to check if its an array
                Jvalue* arr = followPath(root, pathArgs);
                if (arr->getType() == JSONArray) {
                    JsonParser valueParser(value);
                    Jvalue* parsedValue = valueParser.parse(key);
                    static_cast<JsonArray*>(arr)->add(parsedValue);
                }
                else
                {
                    JsonParser valueParser(value);
                    Jvalue* parsedValue = valueParser.parse(key);
                    static_cast<JsonObject*>(target)->add(parsedValue);
                }
            }
            else {
                JsonParser valueParser(value);
                Jvalue* parsedValue = valueParser.parse(key);
                static_cast<JsonObject*>(target)->add(parsedValue);
            }
        }
        else {
            throw std::runtime_error("Cannot add value pair to a non-object or non-array.");
        }

        hasChanges = true;
    }
    catch (const std::exception&)
    {
        throw;
    }
}

void Receiver::move(const std::string& from, const std::string& to) {
    if (jsonContent.empty()) throw std::runtime_error("There is no open file.");
    try
    {

        //parse the JSON string
        ensureParsed();
        //from path
        std::vector<std::string> fromArgs;
        splitPathArgs(from, fromArgs);
        if (fromArgs.empty()) {
            throw std::runtime_error("Invalid from path.");
        }
        //to path
        std::vector<std::string> toArgs;
        splitPathArgs(to, toArgs);
        if (toArgs.empty()) {
            throw std::runtime_error("Invalid to path.");
        }
        //follow path "from"
        Jvalue* fromValue = followPath(root, fromArgs);
        //follow path "to"
        Jvalue* toValue = followPath(root, toArgs);
        //move from fromValue to toValue
        moveValue(root, fromValue, toValue, fromArgs);
        //clears the from location
        clearValue(root, fromArgs);

        hasChanges = true;
    }
    catch (const std::exception&)
    {
        throw;
    } 
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
            obj->removeByKey(keyOrIndexToDelete);
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
            arr->removeByIndex(indexToDelete);
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

void Receiver::moveToArray(Jvalue* array, Jvalue* valueToAdd) {
    if (array->getType() != JSONArray) {
        throw std::invalid_argument("Expected JSONArray type.");
    }

    JsonArray* jsonArray = static_cast<JsonArray*>(array);

    //clone the value to add
    Jvalue* clonedValue = valueToAdd->clone();

    //add the cloned value to the array
    jsonArray->add(clonedValue);
}

Jvalue* Receiver::copyPair(const std::string& key, Jvalue* value, JsonObject* obj) {
    Jvalue* pair = nullptr;

    if (value == nullptr) {
        pair = new(std::nothrow) JsonNull(key);
    }
    else if (value->getType() == JSONBool) {
        pair = new(std::nothrow) JsonBool(*static_cast<JsonBool*>(value));
    }
    else if (value->getType() == JSONNumber) {
        pair = new(std::nothrow) JsonNumber(*static_cast<JsonNumber*>(value));
    }
    else if (value->getType() == JSONString) {
        pair = new(std::nothrow) JsonString(*static_cast<JsonString*>(value));
    }
    else if (value->getType() == JSONArray) {
        pair = new(std::nothrow) JsonArray(*static_cast<JsonArray*>(value));
    }
    else if (value->getType() == JSONObject) {
        pair = new(std::nothrow) JsonObject(*static_cast<JsonObject*>(value));
    }
    else {
        throw std::invalid_argument("Unsupported value type.");
    }

    if (pair == nullptr) {
        throw std::runtime_error("Failed to create key-value pair." +key);
    }

    // Set the key for the new pair
    pair->setKey(key);

    // Add the pair to the object if provided
    if (obj != nullptr) {
        obj->add(pair);
    }

    return pair;
}

void Receiver::moveValue(Jvalue* root, Jvalue* fromValue, Jvalue* toValue, const std::vector<std::string>& fromArgs) {
    //check if toValue exists and is not null
    if (!toValue) {
        throw std::runtime_error("Cannot move: Destination path does not exist.");
    }

    //check if destination is array or object
    if (toValue->getType() == JSONArray) {
        //if the destination is an array, add the value to it
        moveToArray(toValue, fromValue);
    }
    else if (toValue->getType() == JSONObject) {
        //if the destination is an object, create a new key-value pair and add it
        std::string key = fromArgs.back();
        copyPair(key, fromValue, static_cast<JsonObject*>(toValue));
    }
    else {
        throw std::runtime_error("Cannot move: Destination must be an array or object.");
    }
}

void Receiver::clearValue(Jvalue* root, std::vector<std::string>& pathArgs) {
    if (pathArgs.empty()) {
        throw std::runtime_error("Invalid path.");
    }

    std::string key = pathArgs.back();
    std::vector<std::string> parentPathArgs = pathArgs;
    parentPathArgs.pop_back();
    Jvalue* parent = followPath(root, parentPathArgs);

    if (isNumber(key) && parent->getType() == JSONArray) {
        //parent is array 
        size_t index = stoi(key);
        
        JsonArray* arrayParent = static_cast<JsonArray*>(parent);
        arrayParent->removeByIndex(index);
    }
    else if (parent->getType() == JSONObject) {
        JsonObject* objectParent = static_cast<JsonObject*>(parent);
        objectParent->removeByKey(key);
    }
    else {
        throw std::runtime_error("Something went wrond while clearing after moving.");
    }
}

void Receiver::splitPathArgs(const std::string& path, std::vector<std::string>& components) {
    size_t pos = 0;
    size_t start = 0;

    while (pos < path.size()) {
        if (path[pos] == '.' || path[pos] == '[' || path[pos] == ']' || path[pos] == '/') {
            if (pos > start) {
                components.push_back(path.substr(start, pos - start));
            }
            if (path[pos] == '[' || path[pos] == ']' || path[pos] == '.' || path[pos] == '/') {
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

void Receiver::ensureParsed() {
    if (root == nullptr) {
        JsonParser parser(jsonContent);
        root = parser.parse();
    }
}