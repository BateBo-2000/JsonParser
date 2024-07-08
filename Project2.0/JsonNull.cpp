#include "JsonNull.hpp"

JsonNull::JsonNull() {}

JsonNull::JsonNull(const JsonNull& other) {}

void JsonNull::getByValue(const string& str, vector<Jvalue*>& results) {
	if (Utility::matchingPattern(str, "null")) {
		results.push_back(static_cast<Jvalue*>(this));
	}
	return;
}

void JsonNull::getByKey(const string& str, vector<Jvalue*>& results) {
	return; //there is no key
}

const string JsonNull::getType() const {
	return "JNull";
}

JsonNull* JsonNull::clone() const {
	return new JsonNull(*this);
}

string JsonNull::toString() const {
	return "null";
}