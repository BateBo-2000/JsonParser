// get a string and parse it into structure and output a structure
// get a structure and parse it into string
#pragma once
#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include <string>
#include <stdexcept>
#include "Json Types/JValue.hpp"
#include "Json Types/JsonNull.hpp"
#include "Json Types/JsonBool.hpp"
#include "Json Types/JsonNumber.hpp"
#include "Json Types/JsonString.hpp"
#include "Json Types/JsonArray.hpp"
#include "Json Types/JsonObject.hpp"
#include "Exceptions.hpp"

using std::string;

class JsonParser {
public:
	JsonParser(const string& JsonContent);

	Jvalue* parse(); //default arg
	std::string deparse(Jvalue* root);

private:
	size_t index; //really important
	size_t lineNumber;
	const string& JsonContent;

	void skipWhitespace();
	//method to get the current line number
	size_t getCurrentLineNumber() const;
	//extracts string from the JsonContent
	string parseStringFragment();
	bool isDigit(char ch);
	//parses null value
	Jvalue* parseNull();
	//parses bool value
	Jvalue* parseBool();
	//parses numberic value
	Jvalue* parseNumber();
	//parses string value
	Jvalue* parseString();
	//parses array values
	Jvalue* parseArray();
	//parses objects and handles the keys
	Jvalue* parseObject();
	
};

#endif // JSON_PARSER_HPP
