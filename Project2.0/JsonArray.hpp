#pragma once
#ifndef JSON_ARRAY_TYPE_HDD
#define JSON_ARRAY_TYPE_HDD

#include <string>
#include <vector>
#include <stdexcept>
#include "JValue.hpp"
using std::string;
using std::vector;

class JsonArray : public Jvalue {
public:
	JsonArray(const string& key) : key(key), vectorType(JSONNull) {}
	JsonArray(const JsonArray& other) : key(other.key), vectorType(other.vectorType) {
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
	JsonArray& operator=(const JsonArray& other) = delete;
	JsonArray* clone() const override {
		return new JsonArray(*this);
	}
	~JsonArray() {
		for (size_t i = 0; i < value.size(); i++)
		{
			delete value[i];
		}
		value.clear();
	}
	void setKey(const string& newKey) override {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
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
		if (!value.empty() && val->getType() == vectorType) {
			value.push_back(val);
		}
		else if (value.empty()) {
			value.push_back(val);
			vectorType = val->getType();
		}
		else {
			throw std::invalid_argument("Value does not match the array type.");
		}
	}
	void removeByIndex(const size_t index) {
		if (index < value.size()) {
			delete value[index];
			value.erase(value.begin() + index);
		}
		else {
			throw std::out_of_range("Index out of range: cannot erase element.");
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



#endif // !JSON_ARRAY_TYPE_HDD