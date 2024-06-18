#pragma once
#ifndef FILE_UTIL_HDD
#define FILE_UTIL_HDD

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
// this is used to get the path to a file.
class FileUtil {
public:
    void getInputFileLocation(std::string& path);
    void getOutputFileLocation(std::string& path);
};

#endif // !FILE_UTIL_HDD




