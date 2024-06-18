#pragma once
#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>

class Receiver {
public:
    Receiver();

    void readFile(const std::string& filePath);
    void writeFile(const std::string& newFilePath);
    std::string getFileLocation() const;
    bool isValidJson() const;
    void setJsonValue(std::string& json, const std::string& path, const std::string& value);
    void printJson() const;

    //TO DO
    void followPathToDir(std::vector<std::string>& path, size_t& dirStart, size_t& dirEnd);
    //TODO:
    void searchJson(const std::string& json, const std::string& key);
    void containsValue(const std::string& json, const std::string& value);
    std::string getJsonValue(const std::string& json, const std::string& path);
    void createJsonValue(std::string& json, const std::string& path, const std::string& value);
    void deleteJsonValue(std::string& json, const std::string& path);
    void moveJsonValue(std::string& json, const std::string& from, const std::string& to);


private:
    

    std::string trim(const std::string& str);

    std::string jsonContent;
    std::string currentFileLocation;

    
};

#endif // RECEIVER_HPP
