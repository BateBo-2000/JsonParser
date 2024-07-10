#include "../../Header Files/Json Types/JsonNull.hpp"

JsonNull::JsonNull() {}

JsonNull::JsonNull(const JsonNull& other) {}

bool JsonNull::getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) {
	if (Utility::matchingPattern(str, "null")) {
		results.push_back(static_cast<Jvalue*>(this));
		return true;
	}
	return false;
}

void JsonNull::getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch) {
	return; //there is no key
}

bool JsonNull::deleteMember(const string& key) {
	return false; //there are no members
}

bool JsonNull::setValue(const string& key) {
	return false;
}

bool JsonNull::addMember(Jvalue* member, const string& key) {
	return false;	//no members
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