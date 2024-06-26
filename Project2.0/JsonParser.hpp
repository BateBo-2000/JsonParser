// get a string and parse it into structure and output a structure
// get a structure and parse it into string
#pragma once
#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <stdexcept>
#include "JValue.hpp"
#include "JsonNull.hpp"
#include "JsonBool.hpp"
#include "JsonNumber.hpp"
#include "JsonString.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"

using std::string;

class JsonParser {
public:
	JsonParser(const string& file);

	Jvalue* parse(const string& key = ""); //default arg
	std::string deparse(Jvalue* root);

private:
	size_t index; //really important
	size_t lineNumber;
	const string& file;

	void skipWhitespace();
	//method to get the current line number
	size_t getCurrentLineNumber() const;
	//extracts string from the file
	string parseStringFragment();
	bool isDigit(char ch);
	//parses null value
	Jvalue* parseNull(const string& key);
	//parses bool value
	Jvalue* parseBool(const string& key);
	//parses numberic value
	Jvalue* parseNumber(const string& key);
	//parses string value
	Jvalue* parseString(const string& key);
	//parses array values
	Jvalue* parseArray(const string& key);
	//parses objects and handles the keys
	Jvalue* parseObject(const string& key);
	
};

#endif // JSON_PARSER_HPP
