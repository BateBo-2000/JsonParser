#pragma once
#ifndef JSON_BASE_TYPE_HDD
#define JSON_BASE_TYPE_HDD

#include <vector>
#include <string>
using std::string;
using std::vector;

class Jvalue {
public:
	virtual ~Jvalue() = default;
	virtual string toString() const = 0;
	virtual Jvalue* clone() const = 0;
	virtual const string getType() const = 0;
	//the idea is not to use enum so when a new type is added you shouldn't even open the base class.
	virtual bool getByValue(const string& str, vector<Jvalue*>& results, vector<string>& name) = 0;
	virtual void getByKey(const string& str, vector<Jvalue*>& results, vector<string>& name, bool deepSearch = false) = 0;
	//both methods can optionally return the name of the value that the parent has given.
	virtual bool deleteMember(const string& key) = 0;
	virtual bool setValue(const string& key) = 0;
	virtual bool addMember(Jvalue* member, const string& key = string("")) = 0;
};

#endif // !JSON_BASE_TYPE_HDD