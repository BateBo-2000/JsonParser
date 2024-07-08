#pragma once
#ifndef JSON_STRING_TYPE_HDD
#define JSON_STRING_TYPE_HDD

#include <string>
#include <vector>
#include "JValue.hpp"
#include "Utility.hpp"
using std::string;
using std::vector;

class JsonString : public Jvalue {
public:
	JsonString(string value);

	JsonString(const JsonString& other);

	virtual JsonString* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByValue(const string& str, vector<Jvalue*>& results) override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results) override;

	string& getValue();

	void setValue(const string& newValue);

	

private:
	string value;
};



#endif // !JSON_STRING_TYPE_HDD