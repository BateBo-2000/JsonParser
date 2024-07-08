#include "JsonNumber.hpp"

JsonNumber::JsonNumber(double value) :value(value) {}

JsonNumber::JsonNumber(const JsonNumber& other) : value(other.value) {}

JsonNumber* JsonNumber::clone() const {
	return new JsonNumber(*this);
}
const string JsonNumber::getType() const {
	return "JNumber";
}
void JsonNumber::getByValue(const string& str, vector<Jvalue*>& results) {
	if (Utility::matchingPattern(str, toString())) {
		results.push_back(static_cast<Jvalue*>(this));
	}
	return;
}
void JsonNumber::getByKey(const string& str, vector<Jvalue*>& results) {
	return; //there is no key
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