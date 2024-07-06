#pragma once
#ifndef JSON_NULL_TYPE_HDD
#define JSON_NULL_TYPE_HDD

#include <string>
#include "JValue.hpp"
using std::string;

class JsonNull : public Jvalue {
public:
	JsonNull(const string& key) : key(key) {
	}
	JsonNull(const JsonNull& other): key(other.key) {}
	JsonNull* clone() const override {
		return new JsonNull(*this);
	}
	void setKey(const string& newKey) override {
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

#endif // !JSON_NULL_TYPE_HDD