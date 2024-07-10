#include "JsonNumber.hpp"

JsonNumber::JsonNumber(double value) :value(value) {}

JsonNumber::JsonNumber(const JsonNumber& other) : value(other.value) {}

JsonNumber* JsonNumber::clone() const {
	return new JsonNumber(*this);
}

const string JsonNumber::getType() const {
	return "JNumber";
}

bool JsonNumber::getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) {
	if (Utility::matchingPattern(str, toString())) {
		results.push_back(static_cast<Jvalue*>(this));
		return true;
	}
	return false;
}

void JsonNumber::getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch) {
	return; //there is no key
}

bool JsonNumber::deleteMember(const string& key) {
	return false; //there are no members
}

bool JsonNumber::setValue(const string& key) {
	try
	{
		value = std::stod(key);
		return true;
	}
	catch (const std::exception&)
	{
		return false;
	}
}

bool JsonNumber::addMember(Jvalue* member, const string& key) {
	return false;	//no members
}

double JsonNumber::getValue() {
	return value;
}

void JsonNumber::setValue(const double newValue) {
	value = newValue;
}

string JsonNumber::toString() const {
	std::string number = std::to_string(value);
	size_t lastNotZero = number.find_last_not_of('0'); //find last non zero
	if (number[lastNotZero] == '.') {
		return number.substr(0, lastNotZero);
	}
	else {
		return number.substr(0, ++lastNotZero);
	}
}