#include "JsonString.hpp"

JsonString::JsonString(string value) :value(value) {}

JsonString::JsonString(const JsonString& other) : value(other.value) {}

JsonString* JsonString::clone() const {
	return new JsonString(*this);
}

bool JsonString::getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) {
	if (Utility::matchingPattern(str, value)) {
		results.push_back(static_cast<Jvalue*>(this));
		return true;
	}
	return false;
}

void JsonString::getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch) {
	return; //there is no key
}

bool JsonString::deleteMember(const string& key) {
	return false; //there are no members
}

bool JsonString::setValue(const string& key) {
	value = key;
	return true;
}

bool JsonString::addMember(Jvalue* member, const string& key) {
	return false;	//no members
}

const string JsonString::getType() const {
	return "JString";
}
string& JsonString::getValue() {
	return value;
}

string JsonString::toString() const {
	return "\"" + value + "\"";
}