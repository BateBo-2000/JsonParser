#include "JsonObject.hpp"

struct JsonObject::keyValuePair {
	Jvalue* value;
	string key;
	//it is cloning the value so the object is managing its own members
	keyValuePair(const string& k, Jvalue& v) : key(k), value(v.clone()) {}
	keyValuePair(const keyValuePair& other) : key(other.key), value(other.value->clone()) {}

	keyValuePair& operator=(const keyValuePair& other) {
		if (this != &other) {
			key = other.key;
			Jvalue* clonedValue = other.value->clone();
			delete value; //calling it after the clone to not lose data if this throws an exception
			value = clonedValue;
		}
		return *this;
	}
	~keyValuePair() {
		delete value;
	}
};

JsonObject::JsonObject() {}

JsonObject::~JsonObject() {} //vector will call the keyValuePair destructors automatically

JsonObject::JsonObject(const JsonObject& other) {
	for (size_t i = 0; i < other.members.size(); i++)
	{
		members.push_back(other.members[i]);
	}
	//can i just use
	//members = other.members
}

JsonObject& JsonObject::operator=(const JsonObject& other) {
	if (this != &other) {
		members.clear(); //delete the old elements
		for (size_t i = 0; i < other.members.size(); i++)
		{
			members.push_back(other.members[i]);
		}
	}
	return *this;
}

JsonObject* JsonObject::clone() const {
	return new JsonObject(*this);
}

const string JsonObject::getType() const{
	return "JObject";
}

const size_t JsonObject::getSize() const {
	return members.size();
}

bool JsonObject::getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) {
	for (size_t i = 0; i < members.size(); i++)
	{
		size_t initialNames = name.size();

		bool gotIt = members[i].value->getByValue(str, results, name);
		if (gotIt && results.size()-1 == name.size()) {	//if there is a new name therefore the value was primitive and hasnt assigned itself a name.
				name.push_back(members[i].key);			//so here its assigned.
		}
		else if(gotIt && results.size() == name.size()) {
			for (size_t j = initialNames; j < name.size(); j++)
			{
				name[j] = members[i].key + "." + name[j];
			}
		}
	}
	return true; //no need for absolute path or is there?
}



void JsonObject::getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch) {
	for (size_t i = 0; i < members.size(); i++)
	{
		if (Utility::matchingPattern(str, members[i].key, true)) {	
			results.push_back(members[i].value);
			name.push_back(members[i].key);
		}
		else if(deepSearch){
			//search in it if not it
			members[i].value->getByKey(str, results, name, true);
		}
	}
}

bool JsonObject::deleteMember(const string& key) {
	for (size_t i = 0; i < members.size(); ++i) {
		if (Utility::matchingPattern(key, members[i].key)) {	//it workis with wildCards "*". Should be good to leave a warning later.
			members.erase(members.begin() + i);					//to delete specifically the i element.
			i--;
		}
	}
	return true;
}

bool JsonObject::setValue(const string& key) {
	return false;	//cannot really setValue here.
}

bool JsonObject::addMember(Jvalue* member, const string& key) {
	for (size_t i = 0; i < members.size(); i++)
	{
		if (members[i].key == key) {
			throw std::invalid_argument("Element with key " + key + " already exists.");
		}
	}
	members.push_back(keyValuePair(key, *member));
	delete member;
	member = members.back().value;	//make the pointer point towards the cloned value in the obj
	return true;
}

string JsonObject::toString() const{
	string result = "{";
	for (size_t i = 0; i < members.size(); ++i) {
		if (i > 0) result += ", ";
		result += "\"" + members[i].key + "\": " + members[i].value->toString();
	}
	result += "}";
	return result;
}