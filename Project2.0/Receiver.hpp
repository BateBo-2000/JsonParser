#pragma once
#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

#include "FileReader.hpp"
#include "FileWriter.hpp"
#include "JsonParser.hpp"
#include "Utility.hpp"

using std::vector;
using std::string;

class Receiver {
public:
    Receiver();
    ~Receiver();
    bool loadFile(const std::string& filePath, std::string& message);
    bool writeFile(const std::string& newFilePath, std::string& message);
    std::string getFileLocation() const;
    bool isValidJson(std::string& errorMsg);
    const std::string& getJson();
    void searchJson(const std::string& key, std::string& searchResult);
    void deleteJsonValue(const std::string& path);
    void containsValue(const std::string& value, std::string& searchResult);
    void setJsonValue(const std::string& path, const std::string& value);
    void create(const std::string& path, const std::string& value);
    void move(const std::string& from, const std::string& to);
    const bool isChanged() const;

private:
    std::string jsonContent;
    std::string currentFileLocation;
    bool hasChanges;
    Jvalue* root;

    //internal helper functions
    void splitPathArgs(const std::string& path, std::vector<std::string>& components);

    Jvalue* followPath(Jvalue* root, std::vector<std::string> pathArs);
  
    void formatSearchResult(std::string& searchResult, const std::vector<Jvalue*>& jValues);
    
    void ensureParsed();
};

#endif // RECEIVER_HPP
