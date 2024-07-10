#pragma once
#ifndef JSON_NULL_TYPE_HDD
#define JSON_NULL_TYPE_HDD

#include <string>
#include <vector>
#include "JValue.hpp"
#include "../Utility.hpp"
using std::string;
using std::vector;

class JsonNull : public Jvalue {
public:
	JsonNull();

	JsonNull(const JsonNull& other);

	virtual JsonNull* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch = false ) override;

	virtual bool getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name ) override;

	virtual bool deleteMember(const string& key) override;

	virtual bool setValue(const string& key) override;

	virtual bool addMember(Jvalue* member, const string& key = string("")) override;

private:
};

#endif // !JSON_NULL_TYPE_HDD