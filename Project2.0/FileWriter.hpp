//get string and write a file
#pragma once
#ifndef FILE_WRITER_
#define FILE_WRITER_

#include <string>
#include <fstream>
#include <stdexcept>

using std::string;
using std::ofstream;

class FileWriter {
public:
    FileWriter();
    ~FileWriter();

    void writeFile(const string& path, const string& content);

private:
    ofstream outputFile;

    bool isGoodLocation(const std::string& path);
    void open(const string& path);
    void write(const string& content);
    void close();
};

#endif // FILE_WRITER_