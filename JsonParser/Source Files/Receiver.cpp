#include "../Header Files/Receiver.hpp"

Receiver::Receiver() : root(nullptr), hasChanges(false) {}

Receiver::~Receiver() {
    if (root!=nullptr)
    {
        delete root;
    }
}

void Receiver::loadFile(const string& filePath) {
   
    FileReader fileReader;
    try {
        jsonContent.clear();
        fileReader.readFile(filePath, jsonContent);
        //auto saving the location
        currentFileLocation = filePath;
        //clean the old data
        if (root != nullptr) {
            delete root;
            root = nullptr;
        }
        hasChanges = false;

    }
    catch (const std::exception& e) {
        throw ReceiverException(e.what());
    }
}

void Receiver::writeFile(const string& newFilePath) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");

    FileWriter fileWriter;
    try {
        if (hasChanges) {
            JsonParser parser(jsonContent);
            jsonContent = parser.deparse(root);               //deparse
            jsonContent = Utility::prettifyJson(jsonContent); //prettify

        }
        fileWriter.writeFile(newFilePath, jsonContent);
        hasChanges = false;
    }
    catch (const std::invalid_argument&) {
        throw ReceiverException("There is no open file to save.");
    }
    catch (const std::exception& e) {
        throw ReceiverException("Error saving JSON to file: " + string(e.what()));
    }
}

const string& Receiver::getFileLocation() const {
    return currentFileLocation;
}

const bool Receiver::isChanged() const {
    return hasChanges;
}

const string& Receiver::getJson() {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");
    
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

bool Receiver::isValidJson() { //to make it optional to get the error
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");
    try {
        if (root == nullptr) {
            //we dont have changes
            //just try to parse and if all is good save it
            JsonParser parser(jsonContent);
            root = parser.parse();
            return true;  //leave it parsed for future 
        }
        else {
            //there should be strong error checking and typization in the Jvalue classes so it should be fine if its already compiled.
            //other idea: deparse then try to parse again?
            return false;
        }
    }
    catch (const std::exception&) {
        if (root != nullptr) {  //if not valid delete all
            delete root;
            root = nullptr;
        }
        throw;
    }
}

void Receiver::searchJson(const string& key, string& searchResult) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");

    //parse the JSON string
    ensureParsed();

    // Search for the key and collect results
    vector<Jvalue*> results;
    vector<string> names;
    root->getByKey(key, results, names, true);

    //convert from objects to string
    formatSearchResult(searchResult, results, names);
}

void Receiver::containsValue(const string& searchValue, string& searchResult) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");

    //parse the JSON string
    ensureParsed();

    //search for the value and collect results
    vector<Jvalue*> results;
    vector<string> names;
    root->getByValue(searchValue, results, names);

    //convert from objects to string
    formatSearchResult(searchResult, results, names);

}

void Receiver::deleteJsonValue(const string& path) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");

    //parse the JSON string
    ensureParsed();

    //split the path arguments
    vector<string> pathArgs;
    splitPathArgs(path, pathArgs);
    if (pathArgs.empty()) {
        throw ReceiverException("Invalid path.");
    }
    //separate the target and parent
    string target = pathArgs.back();
    pathArgs.pop_back();

    //follow the path to the parent
    Jvalue* parent = followPath(root, pathArgs);

    //delete the key/value pair
    parent->deleteMember(target);

    hasChanges = true;
}

void Receiver::setJsonValue(const string& path, const string& value) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");
    
    //parse the JSON string
    ensureParsed();

    //split the path arguments
    vector<string> pathArgs;
    splitPathArgs(path, pathArgs);
    if (pathArgs.empty()) {
        throw ReceiverException("Invalid path.");
    }

    //followThePath
    Jvalue* target = followPath(root, pathArgs);

    // Set the new value
    bool isOk = target->setValue(value);
    if (!isOk) throw ReceiverException("Cannot to set value " + value + " to " + pathArgs.back());

    hasChanges = true;
}

void Receiver::create(const string& path, const string& value) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");
    //parse the JSON string
    ensureParsed();

    vector<string> pathArgs;
    splitPathArgs(path, pathArgs);

    if (pathArgs.empty()) {
        throw ReceiverException("Invalid path.");
    }
    string key = pathArgs.back();
    pathArgs.pop_back();
    Jvalue* target = followPath(root, pathArgs);

    //parse the value
    JsonParser parser(value);
    Jvalue* member = parser.parse();

    //add the value
    bool isOk = target->addMember(member, key);
    if (!isOk) throw ReceiverException("Cannot add " + value +" to " + pathArgs.back());

    hasChanges = true;
}

void Receiver::move(const string& from, const string& to) {
    if (jsonContent.empty()) throw ReceiverException("There is no open file.");

    //parse the JSON string
    ensureParsed();
    //from path
    vector<string> fromArgs;
    splitPathArgs(from, fromArgs);
    if (fromArgs.empty()) {
        throw ReceiverException("Invalid <from> path.");
    }
    //to path
    vector<string> toArgs;
    splitPathArgs(to, toArgs);
    if (toArgs.empty()) {
        throw ReceiverException("Invalid <to> path.");
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

void Receiver::formatSearchResult(string& searchResult, const vector<Jvalue*>& jValues, const vector<string> names) {
    if (jValues.empty()) {
        //return empty array
        searchResult = "[]";
    }
    else {
        //format the found data
        searchResult += "[";
        if (names.empty()) {
            for (size_t i = 0; i < jValues.size(); ++i) {
                searchResult += jValues[i]->toString() + ",";
            }
        }
        else {
            for (size_t i = 0; i < jValues.size(); ++i) {
                searchResult += "\""+ names[i] + "\" : " + jValues[i]->toString() + ",";
            }
        }
        searchResult.pop_back(); //remove the last comma 
        searchResult += "]";
        searchResult = Utility::prettifyJson(searchResult);
    }
}

void Receiver::splitPathArgs(const string& path, vector<string>& components) {
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
                components.push_back(string(1, path[pos]));
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

Jvalue* Receiver::followPath(Jvalue* root, const vector<string>& pathArs) const {

    if (pathArs.size() == 0) return root;

    if (pathArs.size() == 1 && pathArs[0] == "/") { //handles the root as "/"
         return root;
    }

    vector<Jvalue*> results;
    vector<string> names; //just for the reference. its not used
    Jvalue* current = root;
    for (int i = 0; i < pathArs.size(); i++) {
        results.clear();
        current->getByKey(pathArs[i], results, names, false);
        if (results.empty()) {
            throw ReceiverException("Path does not exist.");
        }
        current = results[0];
    }
    if (!results.empty()) {
        return results[0];
    }
    throw ReceiverException("Final path argument does not exist.");
}

void Receiver::ensureParsed() {
    if (root == nullptr) {
        JsonParser parser(jsonContent);
        root = parser.parse();
    }
}