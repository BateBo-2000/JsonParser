#include "JsonString.hpp"

JsonString::JsonString(string value) :value(value) {}
JsonString::JsonString(const JsonString& other) : value(other.value) {}
JsonString* JsonString::clone() const {
	return new JsonString(*this);
}
void JsonString::getByValue(const string& str, vector<Jvalue*>& results) {
	if (Utility::matchingPattern(str, value)) {
		results.push_back(static_cast<Jvalue*>(this));
	}
	return;
}
void JsonString::getByKey(const string& str, vector<Jvalue*>& results) {
	return; //there is no key
}
const string JsonString::getType() const {
	return "JString";
}
string& JsonString::getValue() {
	return value;
}
void JsonString::setValue(const string& newValue) {
	value = newValue;
}
string JsonString::toString() const {
	return "\"" + value + "\"";
}