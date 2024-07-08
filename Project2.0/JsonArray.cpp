#include "JsonArray.hpp"

JsonArray::JsonArray() {}
JsonArray::~JsonArray() {
	for (size_t i = 0; i < value.size(); i++)
	{
		delete value[i];
	}
	value.clear();
}
JsonArray::JsonArray(const JsonArray& other) {
	for (size_t i = 0; i < other.value.size(); ++i) {
		if (other.value[i]) {
			value.push_back(other.value[i]->clone());
		}
		else {
			value.push_back(nullptr);
		}
	}
}
//it is not used
//JsonArray& JsonArray::operator=(const JsonArray& other) = delete;

JsonArray* JsonArray::clone() const {
	return new JsonArray(*this);
}

const string JsonArray::getType() const {
	return "JArray";
}

const size_t JsonArray::getSize() {
	return value.size();
}

void JsonArray::add(Jvalue* val) {
	if (value.size() == 0) {
		arrayType = val->getType();
		value.push_back(val);
	}
	else if (value.size() != 0 && val->getType() == arrayType) {
		value.push_back(val);
	}
	else {
		throw std::invalid_argument("Value does not match the array type.");
	}
}

void JsonArray::removeByIndex(const size_t index) {
	if (index < value.size()) {
		delete value[index];
		value.erase(value.begin() + index);
	}
	else {
		throw std::out_of_range("Index out of range: cannot erase element.");
	}
}
void JsonArray::getByValue(const string& str, vector<Jvalue*>& results) {
	for (size_t i = 0; i < value.size(); i++)
	{
		value[i]->getByValue(str, results);
	}
}
void JsonArray::getByKey(const string& str, vector<Jvalue*>& results) {
	for (size_t i = 0; i < value.size(); i++)
	{
		value[i]->getByKey(str, results);
	}
}
Jvalue* JsonArray::operator[](size_t index) {
	if (index >= value.size()) {
		throw std::out_of_range("Index out of range");
	}
	return value[index];
}

string JsonArray::toString() const {
	string result = "[";
	for (size_t i = 0; i < value.size(); ++i) {
		if (i > 0) result += ", ";
		result += value[i]->toString();
	}
	result += "]";
	return result;
}