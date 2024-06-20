#pragma once
#ifndef JSON_BASE_TYPE_HDD
#define JSON_BASE_TYPE_HDD

#include <string>
using std::string;

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
	virtual Jvalue* clone() const = 0;
	virtual void setKey(const string& newKey) = 0;
};

#endif // !JSON_BASE_TYPE_HDD