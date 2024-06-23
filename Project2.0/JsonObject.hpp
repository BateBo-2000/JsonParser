#pragma once
#ifndef JSON_OBJECT_TYPE_HDD
#define JSON_OBJECT_TYPE_HDD

#include <string>
#include <vector>
#include <stdexcept>
#include "JValue.hpp"
using std::string;
using std::vector;

class JsonObject : public Jvalue {
public:
	JsonObject(const string& key) : key(key) {}
	JsonObject(const JsonObject& other) {
		for (size_t i = 0; i < other.value.size(); ++i) {
			Jvalue* clonedValue = other.value[i]->clone();
			value.push_back(clonedValue);
		}
	}
	//it is not used
	JsonObject& operator=(const JsonObject& other) = delete;
	JsonObject* clone() const override {
		return new JsonObject(*this);
	}
	~JsonObject() {
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
	JsonType getType() const override {
		return JSONObject;
	}
	const vector<Jvalue*>* getValue() const {
		return &value;
	}
	void add(Jvalue* val) {
		for (size_t i = 0; i < value.size(); i++)
		{
			if (value[i]->getKey() == val->getKey()) {
				throw std::invalid_argument("Element with key "+val->getKey()+" already exists.");
			}
		}
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
				delete value[i];
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



#endif // !JSON_OBJECT_TYPE_HDD