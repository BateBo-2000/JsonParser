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

    void loadFile(const std::string& filePath);
    void writeFile(const std::string& newFilePath);
    std::string getFileLocation() const;
    bool isValidJson(std::string* errorMsg = nullptr) const;
    void setJsonValue(const std::string& path, const std::string& value);
    void printJson() const;
    void searchJson(const std::string& key, std::string& searchResult);
    void deleteJsonValue(const std::string& path);

    //TODO:
    
    void containsValue(const std::string& json, const std::string& value);
    std::string getJsonValue(const std::string& json, const std::string& path);
    void createJsonValue(std::string& json, const std::string& path, const std::string& value);
    void moveJsonValue(std::string& json, const std::string& from, const std::string& to);


private:
    std::string jsonContent;
    std::string currentFileLocation;

    //internal helper functions
    void deleteJsonPairAtTarget(Jvalue* target, const std::string& path);
    void splitPathArgs(const std::string& path, std::vector<std::string>& components);
    Jvalue* followPath(Jvalue* root, std::vector<std::string> pathArs);
    void searchForKey(Jvalue* value, const std::string& key, std::vector<Jvalue*>& results);
    
};

#endif // RECEIVER_HPP
