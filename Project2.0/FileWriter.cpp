#include "FileWriter.hpp"

FileWriter::FileWriter() {}

FileWriter::~FileWriter() {
    close();
}

void FileWriter::writeFile(const string& path, const string& content) {
    open(path);
    if (!outputFile) {
        throw std::runtime_error("File is not open: " + path);
    }

    write(content);
    close();
}

void FileWriter::open(const string& path) {
    outputFile.open(path, std::ios::out);
    if (!outputFile.is_open()) {
        throw std::runtime_error("The file cannot be opened for writing: " + path);
    }
}

void FileWriter::write(const string& content) {
    outputFile.write(content.c_str(), content.size());
    if (!outputFile) {
        throw std::runtime_error("Failed to write to file.");
    }
}

void FileWriter::close() {
    if (outputFile.is_open()) {
        outputFile.close();
    }
}