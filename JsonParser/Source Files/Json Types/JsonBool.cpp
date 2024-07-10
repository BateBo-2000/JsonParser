#include "../../Header Files/Json Types/JsonBool.hpp"

JsonBool::JsonBool(bool value) : value(value) {}

JsonBool::JsonBool(const JsonBool& other) : value(other.value) {}

JsonBool* JsonBool::clone() const {
	return new JsonBool(*this);
}

const string JsonBool::getType() const {
	return "JBool";
}

bool JsonBool::getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) {
	if (Utility::matchingPattern(str, value ? "true" : "false")) {
		results.push_back(static_cast<Jvalue*>(this));
		return true;
	}
	return false;
}

void JsonBool::getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch) {
	return; //there is no key
}

bool JsonBool::deleteMember(const string& key) {
	return false; //there are no members
}

bool JsonBool::setValue(const string& key) {
	if (key == "false") {
		value = false;
		return true;
	}
	else if (key == "true") {
		value = true;
		return true;
	}
	else {
		return false;
	}
}

bool JsonBool::addMember(Jvalue* member, const string& key) {
	return false;	//no members
}

string JsonBool::toString() const {
	return value ? "true" : "false";
}
