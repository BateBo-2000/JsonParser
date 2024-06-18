#include "FileReader.hpp"

FileReader::FileReader() {}

FileReader:: ~FileReader() {
	close();
}

void FileReader::readFile(const string& path, string& fileContents) {
	open(path);
	if (!inputFile) throw std::runtime_error(string("File is not open.") + path);
	load(fileContents, path);
	close();
}

void FileReader::load(string& fileContents, const string& path) {
	//gets the size
	size_t fileSize = getFileSize();
	//resize and dump in
	fileContents.resize(fileSize);
	inputFile.read(&fileContents[0], fileSize + 1);
	//check for errors
	if (!inputFile.eof() || fileSize != fileContents.length()) {
		throw std::runtime_error("Failed to read file: " + path);
	}
}

size_t FileReader::getFileSize() {
	inputFile.seekg(0, std::ios::end);
	size_t fileSize = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);
	return fileSize;
}

void FileReader::open(const string& path) {
	inputFile.open(path, std::ios::in);
	if (!inputFile.is_open())
	{
		throw std::runtime_error(string("The file cannot be opened for reading!\n") + path);
	}
}

void FileReader::close() {
	if (inputFile.is_open()) {
		inputFile.close();
	}
}

