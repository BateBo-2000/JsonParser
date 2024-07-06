#pragma once
#ifndef JSON_NUMBER_TYPE_HDD
#define JSON_NUMBER_TYPE_HDD

#include <string>
#include "JValue.hpp"
using std::string;

class JsonNumber : public Jvalue {
public:
	JsonNumber(const string& key, double value) : key(key), value(value) {}
	JsonNumber(const JsonNumber& other) : value(other.value), key(other.key) {}
	JsonNumber* clone() const override {
		return new JsonNumber(*this);
	}
	void setKey(const string& newKey) override {
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
	void setValue(const double newValue) {
		value = newValue;
	}
	string toString() const override {
		std::string number = std::to_string(value);
		size_t lastNotZero = number.find_last_not_of('0'); //find last non zero
		if (number[lastNotZero] == '.') {
			return number.substr(0, lastNotZero);
		}
		else {
			return number.substr(0, ++lastNotZero);
		}
	}

private:
	double value;
	string key;
};

#endif // !JSON_NUMBER_TYPE_HDD