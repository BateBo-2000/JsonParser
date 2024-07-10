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

	virtual void getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch = false ) override;

	virtual bool getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name ) override;

	virtual bool deleteMember(const string& key) override;

	virtual bool setValue(const string& key) override;

	virtual bool addMember(Jvalue* member, const string& key = string("")) override;

	const size_t getSize() const;

private:
	struct keyValuePair;
	vector<keyValuePair> members;
};



#endif // !JSON_OBJECT_TYPE_HDD