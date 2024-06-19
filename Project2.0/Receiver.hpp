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

class Receiver {
public:
    Receiver();

    void readFile(const std::string& filePath);
    void writeFile(const std::string& newFilePath);
    std::string getFileLocation() const;
    bool isValidJson() const;
    void setJsonValue(const std::string& path, const std::string& value);
    void printJson() const;
    void searchJson(const std::string& key, std::vector<std::string>& searchResult);

    //TO DO
    
    //TODO:
    
    void containsValue(const std::string& json, const std::string& value);
    std::string getJsonValue(const std::string& json, const std::string& path);
    void createJsonValue(std::string& json, const std::string& path, const std::string& value);
    void deleteJsonValue(std::string& json, const std::string& path);
    void moveJsonValue(std::string& json, const std::string& from, const std::string& to);


private:
    void splitPathArgs(const std::string& path, std::vector<std::string>& components);
    Jvalue* followPath(Jvalue* root, const std::string& path);

    std::string jsonContent;
    std::string currentFileLocation;

    
};

#endif // RECEIVER_HPP
