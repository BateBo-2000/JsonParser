#include "../../Header Files/Json Types/JsonArray.hpp"

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

JsonArray* JsonArray::clone() const {
	return new JsonArray(*this);
}

const string JsonArray::getType() const {
	return "JArray";
}

bool JsonArray::getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) {
	bool hasWorked = false;
	for (size_t i = 0; i < value.size(); i++)
	{
		size_t initialNames = name.size();
		bool gotIt = value[i]->getByValue(str, results, name);
		if (gotIt && results.size() - 1 == name.size()) {
			hasWorked = true;
			name.push_back(std::to_string(i));
		}
		else if (gotIt && results.size() == name.size()) {
			for (size_t j = initialNames; j < name.size(); j++)
			{
				name[j] = std::to_string(i) + "." + name[j];
			}
			hasWorked = true;
		}
	}
	return hasWorked;
}

void JsonArray::getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch) {
	if (deepSearch) {
		for (size_t i = 0; i < value.size(); i++)
		{
			value[i]->getByKey(str, results, name, true);
		}
	}
	else {
		try
		{
			size_t index = std::stoi(str);
			results.push_back(value[index]);
			name.push_back(std::to_string(index));
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
		size_t insertPos;
		try
		{
			insertPos = std::stoi(key);
		}
		catch (const std::exception&)
		{
			//cannot convert key to position so default to the back
			insertPos = value.size() - 1;
		}

		if (insertPos < value.size()) {
			value.insert(value.begin() + insertPos, member->clone());	//

			delete member;
			member = value.back();
			return true;
		}
		else {
			throw std::invalid_argument("Index out of bounds.");
		}
	}
	else {
		throw std::invalid_argument("Value type does not match the array type.");
	}
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