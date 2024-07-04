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

class Receiver {
public:
    Receiver();
    ~Receiver();
    bool loadFile(const std::string& filePath, std::string& message);
    bool writeFile(const std::string& newFilePath, std::string& message);
    std::string getFileLocation() const;
    bool isValidJson(std::string* errorMsg = nullptr) const;
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
    void deleteJsonPairAtTarget(Jvalue* target, const std::string& path);
    void splitPathArgs(const std::string& path, std::vector<std::string>& components);
    Jvalue* followPath(Jvalue* root, std::vector<std::string> pathArs);
    void searchJsonKey(Jvalue* root, const std::string& searchKey, std::vector<Jvalue*>& jValues);
    void searchJsonValue(Jvalue* root, const std::string& searchValue, std::vector<Jvalue*>& jValues);
    void formatSearchResult(std::string& searchResult, const std::vector<Jvalue*>& jValues);
    void setValue(Jvalue* target, const std::string& value);
    bool isNumber(const std::string& str);
    void moveValue(Jvalue* root, Jvalue* fromValue, Jvalue* toValue, const std::vector<std::string>& toArgs);
    void moveToArray(Jvalue* array, Jvalue* valueToAdd);
    Jvalue* copyPair(const std::string& key, Jvalue* value, JsonObject* obj);
    void clearValue(Jvalue* root, std::vector<std::string>& pathArgs);
    void ensureParsed();
};

#endif // RECEIVER_HPP
