#pragma once
#ifndef JSON_STRING_TYPE_HDD
#define JSON_STRING_TYPE_HDD

#include <string>
#include "JValue.hpp"

class JsonString : public Jvalue {
public:
	JsonString(const string& key, string value) : key(key), value(value) {}
	JsonString(const JsonString& other) : value(other.value) {}
	JsonString* clone() const override {
		return new JsonString(*this);
	}
	void setKey(const string& newKey) override {
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
	void setValue(const string& newValue) {
		value = newValue;
	}
	string toString() const override {
		return "\"" + value + "\"";
	}

private:
	string value;
	string key;
};



#endif // !JSON_STRING_TYPE_HDD