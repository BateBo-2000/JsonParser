#pragma once
#ifndef JSON_BOOL_TYPE_HDD
#define JSON_BOOL_TYPE_HDD


#include <string>
#include "JValue.hpp"
using std::string;

class JsonBool : public Jvalue {
public:
	JsonBool(const string& key, bool value) : key(key), value(value) {}
	JsonBool(const JsonBool& other) : value(other.value) {}
	JsonBool* clone() const override {
		return new JsonBool(*this);
	}
	void setKey(const string& newKey) override {
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
	void setValue(const bool newValue) {
		value = newValue;
	}
	string toString() const override {
		return value ? "true" : "false";
	}

private:
	bool value;
	string key;
};


#endif // !JSON_BOOL_TYPE_HDD