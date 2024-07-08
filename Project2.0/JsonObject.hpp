#pragma once
#ifndef JSON_OBJECT_TYPE_HDD
#define JSON_OBJECT_TYPE_HDD

#include <string>
#include <vector>
#include <stdexcept>
#include "JValue.hpp"
#include "Utility.hpp"
using std::string;
using std::vector;

class JsonObject : public Jvalue {
public:
	JsonObject();
	~JsonObject();
	JsonObject(const JsonObject& other);
	JsonObject& operator=(const JsonObject& other);

	virtual JsonObject* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByValue(const string& str, vector<Jvalue*>& results) override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results) override;

	const size_t getSize() const;

	void add(string& key, Jvalue& val);

	void removeByKey(const string& key);

private:
	struct keyValuePair;
	vector<keyValuePair> members;
};



#endif // !JSON_OBJECT_TYPE_HDD