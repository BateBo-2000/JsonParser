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

	JsonArray& operator=(const JsonArray& other) = delete;

	virtual JsonArray* clone() const override;

	virtual string toString() const override;

	virtual const string getType() const override;

	virtual void getByValue(const string& str, vector<Jvalue*>& results) override;

	virtual void getByKey(const string& str, vector<Jvalue*>& results) override;

	const size_t getSize();

	void add(Jvalue* val);

	void removeByIndex(const size_t index);

	Jvalue* operator[](size_t index);

private:
	vector<Jvalue*> value;
	string arrayType;
};



#endif // !JSON_ARRAY_TYPE_HDD