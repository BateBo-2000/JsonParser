#include "JsonBool.hpp"

JsonBool::JsonBool(bool value) : value(value) {}

JsonBool::JsonBool(const JsonBool& other) : value(other.value) {}

JsonBool* JsonBool::clone() const {
	return new JsonBool(*this);
}

const string JsonBool::getType() const {
	return "JBool";
}

void JsonBool::getByValue(const string& str, vector<Jvalue*>& results) {
	if (Utility::matchingPattern(str, value ? "true" : "false")) {
		results.push_back(static_cast<Jvalue*>(this));
	}
	return;
}

void JsonBool::getByKey(const string& str, vector<Jvalue*>& results) {
	return; //there is no key
}

bool JsonBool::getValue() {
	return value;
}

void JsonBool::setValue(const bool newValue) {
	value = newValue;
}

string JsonBool::toString() const {
	return value ? "true" : "false";
}
