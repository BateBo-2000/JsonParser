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

JsonArray& JsonArray::operator=(const JsonArray& other) {
	if (this != &other){
		value.clear();
		for (size_t i = 0; i < other.value.size(); i++)
		{
			value.push_back(other.value[i]->clone());
		}
	}
	return *this;
}

JsonArray* JsonArray::clone() const {
	return new JsonArray(*this);
}

const string JsonArray::getType() const {
	return "JArray";
}

const size_t JsonArray::getSize() {
	return value.size();
}

void JsonArray::getByValue(const string& str, vector<Jvalue*>& results) {
	for (size_t i = 0; i < value.size(); i++)
	{
		value[i]->getByValue(str, results);
	}
}

void JsonArray::getByKey(const string& str, vector<Jvalue*>& results, bool deepSearch) {
	if (deepSearch) {
		for (size_t i = 0; i < value.size(); i++)
		{
			value[i]->getByKey(str, results);
		}
	}
	else {
		try
		{
			size_t index = std::stoi(str);
			results.push_back(value[index]);
		}
		catch (const std::exception&)
		{
			return; // cannot convert it to number
		}
	}
	return; //no keys
}

bool JsonArray::deleteMember(const string& key) {
	try
	{
		size_t index = std::stoi(key);
		if (index < value.size()) {
			value.erase(value.begin() + index);
			return true;
		}
		else {
			throw std::out_of_range("Index out of range: cannot erase element.");
		}
	}
	catch (const std::exception&)
	{
		throw std::invalid_argument(key + " is not a number.");
	}
}

bool JsonArray::setValue(const string& key) {
	return false; //cant really set value here
}

bool JsonArray::addMember(Jvalue* member, const string& key) {
	if (value.size() == 0) {
		value.push_back(member->clone());

		delete member;			
		member = value.back();	//now the value is pointing towards its copy in the array.
		return true;
	}
	else if (value.size() != 0 && member->getType() == value[0]->getType()) {	//the type is determined by the first element
		value.push_back(member->clone());

		delete member;
		member = value.back();
		return true;
	}
	else {
		throw std::invalid_argument("Value type does not match the array type.");
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