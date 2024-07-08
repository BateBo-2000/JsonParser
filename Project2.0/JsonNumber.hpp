#pragma once
#ifndef JSON_NUMBER_TYPE_HDD
#define JSON_NUMBER_TYPE_HDD

#include <string>
#include <vector>
#include "JValue.hpp"
#include "Utility.hpp"
using std::string;
using std::vector;

class JsonNumber : public Jvalue {
public:
	JsonNumber(double value);

	JsonNumber(const JsonNumber& other);

	virtual JsonNumber* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByValue(const string& str, vector<Jvalue*>& results) override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results) override;

	double getValue();

	void setValue(const double newValue);

private:
	double value;
};

#endif // !JSON_NUMBER_TYPE_HDD