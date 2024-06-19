#include "Utility.hpp"

std::string Utility::prettifyJson(const std::string& input) {
	std::string output;
	bool inQuote = false;
	int numSpaces = 0;

	for (char c : input) {
		switch (c) {
		case '{':
		case '[':
			output += c;
			output += '\n';
			numSpaces += 4;
			output += std::string(numSpaces, ' ');
			break;
		case '}':
		case ']':
			output += '\n';
			numSpaces -= 4;
			output += std::string(numSpaces, ' ');
			output += c;
			break;
		case ',':
			output += c;
			if (!inQuote) {
				output += '\n';
				output += std::string(numSpaces, ' ');
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