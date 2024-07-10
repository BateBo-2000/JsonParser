#pragma once
#ifndef FILE_READER_
#define FILE_READER_

#include <string>
#include <fstream>
#include <stdexcept>

using std::string;
using std::ifstream;

class FileReader {
public:
	FileReader();
	~FileReader();

	void readFile(const string& path, string& fileContents);

private:
	ifstream inputFile;

	void load(string& fileContents, const string& path);
	void open(const string& path);
	size_t getFileSize();
	void close();
};

#endif // !FILE_READER_
