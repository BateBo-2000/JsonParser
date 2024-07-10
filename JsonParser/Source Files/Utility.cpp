#include "../Header Files/Utility.hpp"

string Utility::prettifyJson(const string& input) {
	string output;
	bool inQuote = false;
	int numSpaces = 0;

	for (char c : input) {
		switch (c) {
		case '{':
		case '[':
			output += c;
			output += '\n';
			numSpaces += 4;
			output += string(numSpaces, ' ');
			break;
		case '}':
		case ']':
			output += '\n';
			numSpaces -= 4;
			output += string(numSpaces, ' ');
			output += c;
			break;
		case ',':
			output += c;
			if (!inQuote) {
				output += '\n';
				output += string(numSpaces, ' ');
			}
			break;
		case '\"':
			output += c;
			inQuote = !inQuote;
			break;
		case ':':
			output += ": ";
			break;
		case ' ':
			if (inQuote) {
				output += c;
			}
			break;
		default:
			output += c;
			break;
		}
	}

	return output;
}

//helper for searching
bool Utility::matchingPattern(const string& str, const string& value, bool startsWith){
	bool wildCard = str.back() == '*';
	if (!wildCard) {
		return value == str;
	}
	else {
		string pattern = str;
		pattern.pop_back();
		if (startsWith) {
			return value.starts_with(pattern);
		}
		else {
			return value.find(pattern) != std::string::npos;
		}
	}
}