// Receiver.hpp
#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <string>
#include <vector>
#include <stdexcept>

class Receiver {
public:
    Receiver();

    void readFile(const std::string& filePath);
    void writeFile(const std::string& newFilePath);
    std::string getFileLocation() const;
    bool isValidJson() const;
    void setJsonValue(std::string& json, const std::string& path, const std::string& value);

    //TODO:
    void printJson() const;
    void searchJson(const std::string& json, const std::string& key);
    void containsValue(const std::string& json, const std::string& value);
    

private:
    
    std::string getJsonValue(const std::string& json, const std::string& path);

    void createJsonValue(std::string& json, const std::string& path, const std::string& value);
    void deleteJsonValue(std::string& json, const std::string& path);
    void moveJsonValue(std::string& json, const std::string& from, const std::string& to);
    std::string trim(const std::string& str);

    std::string jsonContent;
    std::string currentFileLocation;
};

#endif // RECEIVER_HPP
