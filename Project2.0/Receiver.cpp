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
        jsonContent.clear();
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
        if (hasChanges) {
            JsonParser parser(jsonContent);
            jsonContent = parser.deparse(root);               //deparse
            jsonContent = Utility::prettifyJson(jsonContent); //prettify

        }
        fileWriter.writeFile(newFilePath, jsonContent);
        message = "JSON saved to file: " + newFilePath;

        hasChanges = false;
        return true;
    }
    catch (const std::invalid_argument&) {
        message = "There is no open file to save.";
        return false;
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
        vector<Jvalue*> results;
        root->getByKey(key, results, true);

        //convert from objects to string
        formatSearchResult(searchResult, results);
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
        std::vector<Jvalue*> results;
        root->getByValue(searchValue, results);
        //searchJsonValue(root, searchValue, jValues);

        //convert from objects to string
        formatSearchResult(searchResult, results);
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
        parent->deleteMember(target);

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
        bool isOk = target->setValue(value);
        if (!isOk) throw std::invalid_argument("Cannot to set value " + value + " to " + pathArgs.back());

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

        //parse the value
        JsonParser parser(value);
        Jvalue* member = parser.parse();

        //add the value
        bool isOk = target->addMember(member, key);
        if (!isOk) throw std::invalid_argument("Cannot add " + value +" to " + pathArgs.back());

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
            throw std::runtime_error("Invalid <from> path.");
        }
        //to path
        std::vector<std::string> toArgs;
        splitPathArgs(to, toArgs);
        if (toArgs.empty()) {
            throw std::runtime_error("Invalid <to> path.");
        }
        //follow path "from"
        Jvalue* fromValue = followPath(root, fromArgs);
        //follow path "to"
        Jvalue* toValue = followPath(root, toArgs);

        Jvalue* tempCopy = fromValue->clone();
        //get the key if any
        string key = fromArgs.back();
        fromArgs.pop_back();
        //copy the new instance
        toValue->addMember(tempCopy, key);
        //delete the old instance
        Jvalue* parent = followPath(root, fromArgs);
        parent->deleteMember(key);

        hasChanges = true;
    }
    catch (const std::exception&)
    {
        throw;
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
            searchResult += jValues[i]->toString() + ",";
        }
        searchResult.pop_back(); //remove the last comma 
        searchResult += "]";
        searchResult = Utility::prettifyJson(searchResult);
    }
}

void Receiver::splitPathArgs(const std::string& path, std::vector<std::string>& components) {
    size_t pos = 0;
    size_t start = 0;

    if (path[0] == '/') {                //this is handling root
        components.push_back("/");
    }

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

    if (pathArs.size() == 0) return root;

    if (pathArs.size() == 1 && pathArs[0] == "/") { //handles the root as "/"
         return root;
    }

    vector<Jvalue*> results;
    Jvalue* current = root;
    for (int i = 0; i < pathArs.size(); i++) {
        results.clear();
        current->getByKey(pathArs[i], results);
        if (results.empty()) {
            throw std::invalid_argument("Path does not exist.");
        }
        current = results[0];
    }
    if (!results.empty()) {
        return results[0];
    }
    throw std::invalid_argument("Final path argument does not exist.");
}

void Receiver::ensureParsed() {
    if (root == nullptr) {
        JsonParser parser(jsonContent);
        root = parser.parse();
    }
}