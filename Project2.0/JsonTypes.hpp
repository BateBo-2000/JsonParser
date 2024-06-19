#pragma once
#ifndef JSON_TYPES_HDD
#define JSON_TYPES_HDD

#include <vector>
#include <string>
#include <stdexcept>
using std::string;
using std::vector;

enum JsonType
{
	JSONNull,
	JSONBool,
	JSONNumber,
	JSONString,
	JSONArray,
	JSONObject
};

class Jvalue {
public:
	virtual ~Jvalue() = default;
	virtual JsonType getType() const = 0;
	virtual const string& getKey() const = 0;
	virtual string toString() const = 0;
};

class JsonObject : public Jvalue {
public:
	JsonObject(const string& key) : key(key) {}
	~JsonObject() {
		for (Jvalue* val : value) {
			delete val;
		}
	}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONObject;
	}
	const vector<Jvalue*>* getValue() const {
		return &value;
	}
	void add(Jvalue* val) {
		value.push_back(val);
	}
	Jvalue* getByExactKey(const std::string& key) {
		bool useExact = key.back() != '*';
		for (size_t i = 0; i < value.size(); ++i) {
			if (useExact && value[i]->getKey() == key) {
				//it can return on the first found because a key duplication is error in json
				return value[i];
			}
			else if (!useExact && value[i]->getKey().find(key.substr(0, key.size() - 1)) != std::string::npos) {
				return value[i];
			}
		}
		return nullptr;
	}
	std::vector<Jvalue*> getByKey(const std::string& key) {
		std::vector<Jvalue*> results;
		bool beExact = key.back() != '*';

		for (size_t i = 0; i < value.size(); ++i) {
			const std::string& currentKey = value[i]->getKey();

			if (beExact && currentKey == key) {
				results.push_back(value[i]);
			}
			else if (!beExact && currentKey.find(key.substr(0, key.size() - 1)) != std::string::npos) {
				results.push_back(value[i]);
			}
		}
		return results;
	}
	std::vector<Jvalue*> getByValue(const std::string& searchValue) {
		std::vector<Jvalue*> results;
		bool beExact = searchValue.back() != '*';

		for (size_t i = 0; i < value.size(); ++i) {
			// to avoid stringifying and returning whole objects and arrays
			if (value[i]->getType() != JSONArray && value[i]->getType() != JSONObject) { 
				if (beExact && value[i]->toString() == searchValue) {
					results.push_back(value[i]);
				}
				else if (!beExact && value[i]->toString().find(searchValue.substr(0, searchValue.size() - 1)) != std::string::npos) {
					results.push_back(value[i]);
				}
			}	
		}
		return results;
	}
	void removeByKey(const std::string& key) {
		for (size_t i = 0; i < value.size(); ++i) {
			if (value[i]->getKey() == key) {
				value.erase(value.begin() + i);
				return;
			}
		}
		throw std::runtime_error("Key not found: cannot erase element");
	}
	string toString() const override {
		string result = "{";
		for (size_t i = 0; i < value.size(); ++i) {
			if (i > 0) result += ", ";
			result += "\"" + value[i]->getKey() + "\": " + value[i]->toString();
		}
		result += "}";
		return result;
	}

private:
	//in this case these are the key value pairs in the object
	vector<Jvalue*> value;
	string key;
};

class JsonArray : public Jvalue {
public:
	JsonArray(const string& key) : key(key), vectorType(JSONNull) {}
	~JsonArray() {
		for (Jvalue* val : value) {
			delete val;
		}
	}
	void setKey(const string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	void setType(JsonType type) {
		vectorType = type;
	}
	JsonType getType() const override {
		return JSONArray;
	}
	JsonType getArrayType() const {
		return vectorType;
	}
	const vector<Jvalue*>& getValue() const {
		return value;
	}
	void add(Jvalue* val) {
		value.push_back(val);
	}
	void removeByIndex(const size_t index) {
		if (index < value.size()) {
			value.erase(value.begin() + index);
		}
		else {
			throw std::runtime_error("Index out of range: cannot erase element");
		}
	}
	std::vector<Jvalue*> getByValue(const std::string& searchValue) {
		std::vector<Jvalue*> results;
		bool beExact = searchValue.back() != '*';

		for (size_t i = 0; i < value.size(); ++i) {
			if (value[i]->getType() != JSONArray && value[i]->getType() != JSONObject) {
				if (beExact && value[i]->toString() == searchValue) {
					results.push_back(value[i]);
				}
				else if (!beExact && value[i]->toString().find(searchValue.substr(0, searchValue.size() - 1)) != std::string::npos) {
					results.push_back(value[i]);
				}
			}
		}
		return results;
	}
	Jvalue* operator[](size_t index) {
		if (index >= value.size()) {
			throw std::out_of_range("Index out of range");
		}
		return value[index];
	}
	string toString() const override {
		string result = "[";
		for (size_t i = 0; i < value.size(); ++i) {
			if (i > 0) result += ", ";
			result += value[i]->toString();
		}
		result += "]";
		return result;
	}
private:
	vector<Jvalue*> value;
	JsonType vectorType;
	string key;
};

class JsonString : public Jvalue {
public:
	JsonString(const string& key, string value) : key(key), value(value) {}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONString;
	}
	string& getValue() {
		return value;
	}
	void setValue(string& newValue) {
		value = newValue;
	}
	string toString() const override {
		return "\"" + value + "\"";
	}

private:
	string value;
	string key;
};

class JsonNumber : public Jvalue {
public:
	JsonNumber(const string& key, double value) : key(key), value(value) {}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONNumber;
	}
	double getValue() {
		return value;
	}
	void setValue(double newValue) {
		value = newValue;
	}
	string toString() const override {
		return std::to_string(value);
	}

private:
	double value;
	string key;
};

class JsonBool : public Jvalue {
public:
	JsonBool(const string& key, bool value) : key(key), value(value) {}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONBool;
	}
	bool getValue() {
		return value;
	}
	void setValue(bool newValue) {
		value = newValue;
	}
	string toString() const override {
		return value ? "true" : "false";
	}

private:
	bool value;
	string key;
};

class JsonNull : public Jvalue {
public:
	JsonNull(const string& key) : key(key) {
	}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const  override {
		return JSONNull;
	}
	string toString() const override {
		return "null";
	}

private:
	string key;
};

#endif // !JSON_TYPES_HDD