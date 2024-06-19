#include <vector>
#include <string>
#include <stdexcept>
using std::string;
using std::vector;

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
};

class JsonObject : public Jvalue {
public:
	JsonObject(const string& key) : key(key) {}
	~JsonObject() {
		for (Jvalue* val : value) {
			delete val;
		}
	}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONObject;
	}
	const vector<Jvalue*>* getValue() const {
		return &value;
	}
	void add(Jvalue* val) {
		value.push_back(val);
	}
	Jvalue* getByKey(const std::string& key) {
		for (size_t i = 0; i < value.size(); ++i) {
			if (value[i]->getKey() == key) {
				return value[i];
			}
		}
		return nullptr; // Return nullptr if key is not found
	}
	void removeByKey(const std::string& key) {
		for (size_t i = 0; i < value.size(); ++i) {
			if (value[i]->getKey() == key) {
				value.erase(value.begin() + i);
				return;
			}
		}
		throw std::runtime_error("Key not found: cannot erase element");
	}
	string toString() const override {
		string result = "{";
		for (size_t i = 0; i < value.size(); ++i) {
			if (i > 0) result += ", ";
			result += "\"" + value[i]->getKey() + "\": " + value[i]->toString();
		}
		result += "}";
		return result;
	}

private:
	//in this case these are the key value pairs in the object
	vector<Jvalue*> value;
	string key;
};

class JsonArray : public Jvalue {
public:
	JsonArray(const string& key) : key(key), vectorType(JSONNull) {}
	~JsonArray() {
		for (Jvalue* val : value) {
			delete val;
		}
	}
	void setKey(const string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	void setType(JsonType type) {
		vectorType = type;
	}
	JsonType getType() const override {
		return JSONArray;
	}
	JsonType getArrayType() const {
		return vectorType;
	}
	const vector<Jvalue*>& getValue() const {
		return value;
	}
	void add(Jvalue* val) {
		value.push_back(val);
	}
	void remove(const size_t index) {
		if (index < value.size()) {
			value.erase(value.begin() + index);
		}
		else {
			throw std::runtime_error("Index out of range: cannot erase element");
		}
	}
	Jvalue* operator[](size_t index) {
		if (index >= value.size()) {
			throw std::out_of_range("Index out of range");
		}
		return value[index];
	}
	string toString() const override {
		string result = "[";
		for (size_t i = 0; i < value.size(); ++i) {
			if (i > 0) result += ", ";
			result += value[i]->toString();
		}
		result += "]";
		return result;
	}
private:
	vector<Jvalue*> value;
	JsonType vectorType;
	string key;
};

class JsonString : public Jvalue {
public:
	JsonString(const string& key, string value) : key(key), value(value) {}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONString;
	}
	string& getValue() {
		return value;
	}
	void setValue(string& newValue) {
		value = newValue;
	}
	string toString() const override {
		return "\"" + value + "\"";
	}

private:
	string value;
	string key;
};

class JsonNumber : public Jvalue {
public:
	JsonNumber(const string& key, double value) : key(key), value(value) {}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONNumber;
	}
	double getValue() {
		return value;
	}
	void setValue(double newValue) {
		value = newValue;
	}
	string toString() const override {
		return std::to_string(value);
	}

private:
	double value;
	string key;
};

class JsonBool : public Jvalue {
public:
	JsonBool(const string& key, bool value) : key(key), value(value) {}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const override {
		return JSONBool;
	}
	bool getValue() {
		return value;
	}
	void setValue(bool newValue) {
		value = newValue;
	}
	string toString() const override {
		return value ? "true" : "false";
	}

private:
	bool value;
	string key;
};

class JsonNull : public Jvalue {
public:
	JsonNull(const string& key) : key(key) {
	}
	void setKey(string& newKey) {
		key = newKey;
	}
	const string& getKey() const override {
		return key;
	}
	JsonType getType() const  override {
		return JSONNull;
	}
	string toString() const override {
		return "null";
	}

private:
	string key;
};

