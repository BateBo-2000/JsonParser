#include "../Header Files/JsonParser.hpp"

JsonParser::JsonParser(const string& JsonContent) : JsonContent(JsonContent), index(0), lineNumber(0) {
	if (JsonContent.empty()) {
		throw std::invalid_argument("No JSON content found. Line:" + std::to_string(getCurrentLineNumber()));
	}
}

Jvalue* JsonParser::parse() {
	skipWhitespace(); // Skip any whitespace characters

	if (index >= JsonContent.size()) {
		throw std::invalid_argument("Empty JSON string. Line:" + std::to_string(getCurrentLineNumber()));
	}

	char ch = JsonContent[index];
	if (ch == 'n') {
		return parseNull();
	}
	else if (ch == 't' || ch == 'f') {
		return parseBool();
	}
	else if (isdigit(ch) || ch == '-') {
		return parseNumber();
	}
	else if (ch == '"') {
		return parseString();
	}
	else if (ch == '[') {
		return parseArray();
	}
	if (ch == '{') {
		return parseObject();
	}
	else {
		throw std::invalid_argument("Invalid JSON format. Line:" + std::to_string(getCurrentLineNumber()));
	}
}

std::string JsonParser::deparse(Jvalue* root) {
	if (!root) {
		throw std::invalid_argument("Root is null.");
	}
	return root->toString();
}

void JsonParser::skipWhitespace() {
	while (index < JsonContent.size() && (JsonContent[index] == ' ' || JsonContent[index] == '\t' || JsonContent[index] == '\n' || JsonContent[index] == '\r')) {
		if (JsonContent[index] == '\n') {
			++lineNumber;
		}
		++index;
	}
}

size_t JsonParser::getCurrentLineNumber() const {
	return lineNumber;
}

string JsonParser::parseStringFragment() {
	string result;
	while (index < JsonContent.size()) {
		char ch = JsonContent[++index];
		if (ch == '"') {
			return result;
		}
		else {
			result += ch;
		}
	}
	throw std::invalid_argument("Invalid JSON format: unterminated string. Line:" + std::to_string(getCurrentLineNumber()));
}

bool JsonParser::isDigit(char ch) {
	return (ch >= '0' && ch <= '9');
}

Jvalue* JsonParser::parseNull() {
	//check if the next characters in JsonContent are "null"
	if (JsonContent.substr(index, 4) == "null") {
		index += 4; // Move index past "null"
		return new JsonNull();
	}
	else {
		throw std::invalid_argument("Invalid JSON format: expected 'null'. Line:" + std::to_string(getCurrentLineNumber()));
	}
}

Jvalue* JsonParser::parseBool() {
	if (JsonContent.substr(index, 4) == "true") {
		index += 4;
		return new JsonBool(true);
	}
	else if (JsonContent.substr(index, 5) == "false") {
		index += 5;
		return new JsonBool(false);
	}
	throw std::invalid_argument("Invalid JSON format: expected 'true' or 'false'. Line:" + std::to_string(getCurrentLineNumber()));
}

Jvalue* JsonParser::parseNumber() {
	size_t start = index;
	bool hasDecimal = false;
	while (index < JsonContent.size() && (isDigit(JsonContent[index]) || JsonContent[index] == '.')) {
		++index;
		if (JsonContent[index] == '.') {
			if (hasDecimal) {
				throw std::invalid_argument("Invalid JSON format: multiple decimal points or decimal point after exponent. Line:" + std::to_string(getCurrentLineNumber()));
			}
			hasDecimal = true;
		}
	}
	std::string numberStr = JsonContent.substr(start, index - start);
	double value = stod(numberStr);
	return new JsonNumber(value);
}

Jvalue* JsonParser::parseString() {
	if (JsonContent[index] != '"') {
		throw std::invalid_argument("Invalid JSON format: expected '\"'. Line:" + std::to_string(getCurrentLineNumber()));
	}
	// reusing the method for reading names
	std::string value = parseStringFragment();
	if (JsonContent[index] != '"') {
		throw std::invalid_argument("Invalid JSON format: expected '\"'. Line:" + std::to_string(getCurrentLineNumber()));
	}
	index++;
	return new JsonString(value);
}

Jvalue* JsonParser::parseArray() {

	JsonArray* arr = new JsonArray(); //create a new JsonArray object

	if (JsonContent[index] == '[') {
		++index;
	}
	skipWhitespace();
	bool firstElement = true;	//for tracking ","
	while (index < JsonContent.size() && JsonContent[index] != ']') {
		//no need to handle names because the values are accessed with indexing
		skipWhitespace();
		if (!firstElement) {
			if (JsonContent[index] != ',') {
				delete arr;
				throw std::invalid_argument("Invalid JSON format: expected ','. Line:" + std::to_string(getCurrentLineNumber()));
			}
			++index;
			skipWhitespace();
		}
		firstElement = false;

		Jvalue* val = parse();
		try
		{
			arr->addMember(val);
		}
		catch (const std::exception& e)
		{
			delete arr;
			throw std::invalid_argument("Invalid JSON format: "+ string(e.what()) + " Line:" + std::to_string(getCurrentLineNumber()));
		}
		skipWhitespace();
	}

	if (index >= JsonContent.size()) {
		delete arr;
		throw std::invalid_argument("Invalid JSON format: unterminated array. Expected ']' Line:" + std::to_string(getCurrentLineNumber()));
	}
	++index; //move past the closing bracket "]"
	skipWhitespace();
	return arr;
}

Jvalue* JsonParser::parseObject() {
	JsonObject* obj = new JsonObject();
	if (JsonContent[index] == '{') {
		++index;
	}
	while (index < JsonContent.size() && JsonContent[index] != '}') {
		skipWhitespace();

		//handling the key
		if (JsonContent[index] != '"') {
			delete obj;
			throw std::invalid_argument("Invalid JSON format: expected '\"'. Line:" + std::to_string(getCurrentLineNumber()));
		}
		string nestedKey = parseStringFragment();
		if (JsonContent[index] != '"') {
			delete obj;
			throw std::invalid_argument("Invalid JSON format: expected '\"'. Line:" + std::to_string(getCurrentLineNumber()));
		}
		++index;

		skipWhitespace();

		//handle the value
		if (JsonContent[index] != ':') {
			delete obj;
			throw std::invalid_argument("Invalid JSON format: expected ':'. Line:" + std::to_string(getCurrentLineNumber()));
		}
		++index;

		skipWhitespace();

		Jvalue* val = parse();
		obj->addMember(val, nestedKey);

		skipWhitespace();

		//handle multiple nested types (just checks the comma)
		if (JsonContent[index] == ',') {
			++index;
		}
		else if (JsonContent[index] != '}') {	//if there is no comma there should be a "}"
			delete obj;
			throw std::invalid_argument("Invalid JSON format: expected ',' or '}'. Line:" + std::to_string(getCurrentLineNumber()));
		}
	}

	//ensures that we have found the "}" and not the end of the string
	if (index >= JsonContent.size() || JsonContent[index] != '}') {
		delete obj;
		throw std::invalid_argument("Invalid JSON format: unterminated object. Line:" + std::to_string(getCurrentLineNumber()));
	}
	++index; //move past '}'
	skipWhitespace();
	return obj;
}
