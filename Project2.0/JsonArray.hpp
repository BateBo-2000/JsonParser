#pragma once
#ifndef JSON_ARRAY_TYPE_HDD
#define JSON_ARRAY_TYPE_HDD

#include <string>
#include <vector>
#include <stdexcept>
#include "JValue.hpp"
using std::string;
using std::vector;

class JsonArray : public Jvalue {
public:
	JsonArray();

	~JsonArray();
	
	JsonArray(const JsonArray& other);

	JsonArray& operator=(const JsonArray& other);

	virtual JsonArray* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch = false ) override;

	virtual bool getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name ) override;

	virtual bool deleteMember(const string& key) override;

	virtual bool setValue(const string& key) override;

	virtual bool addMember(Jvalue* member, const string& key = string("")) override;

	const size_t getSize();

	Jvalue* operator[](size_t index);

private:
	vector<Jvalue*> value;
};



#endif // !JSON_ARRAY_TYPE_HDD