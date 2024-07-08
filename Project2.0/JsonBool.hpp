#pragma once
#ifndef JSON_BOOL_TYPE_HDD
#define JSON_BOOL_TYPE_HDD

#include <string>
#include <vector>
#include "JValue.hpp"
#include "Utility.hpp"
using std::string;
using std::vector;

class JsonBool : public Jvalue {
public:
	JsonBool(bool value);

	JsonBool(const JsonBool& other);

	virtual JsonBool* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByValue(const string& str, vector<Jvalue*>& results) override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results) override;

	bool getValue();

	void setValue(const bool newValue);

private:
	bool value;
};


#endif // !JSON_BOOL_TYPE_HDD