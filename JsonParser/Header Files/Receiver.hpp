#pragma once
#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "File Handlers/FileReader.hpp"
#include "File Handlers/FileWriter.hpp"
#include "JsonParser.hpp"
#include "Utility.hpp"

using std::vector;
using std::string;

class Receiver {
public:
    Receiver();
    ~Receiver();
    bool loadFile(const string& filePath, string& message);
    bool writeFile(const string& newFilePath, string& message);
    const string& getFileLocation() const;
    bool isValidJson(string& errorMsg);
    const string& getJson();
    void searchJson(const string& key, string& searchResult);
    void deleteJsonValue(const string& path);
    void containsValue(const string& value, string& searchResult);
    void setJsonValue(const string& path, const string& value);
    void create(const string& path, const string& value);
    void move(const string& from, const string& to);
    const bool isChanged() const;

private:
    string jsonContent;
    string currentFileLocation;
    bool hasChanges;
    Jvalue* root;

    //internal helper functions
    void splitPathArgs(const string& path, vector<string>& components);

    Jvalue* followPath(Jvalue* root, const vector<string>& pathArs) const;
  
    void formatSearchResult(string& searchResult, const vector<Jvalue*>& jValues, const vector<string> names = vector<string>());
    
    void ensureParsed();
};

#endif // RECEIVER_HPP
