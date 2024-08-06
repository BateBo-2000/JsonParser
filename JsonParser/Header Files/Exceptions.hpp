#pragma once
#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

using std::exception;
using std::string;

class ReceiverException : public exception {
public:
	ReceiverException(const string& message);
	ReceiverException(const string& message, const std::exception& e);
	//The internet said to make it noexcept.
	virtual const char* what() const noexcept;
private:
	const string message;
	const string nestedException;
	string fullErrorMessage;
};

class InvokerException : public exception {
public:
	InvokerException(const string& message);
	virtual const char* what() const noexcept;
private:
	const string message;
};

class CommandException : public exception {
public:
	CommandException(const string& message);
	virtual const char* what() const noexcept;
private:
	const string message;
};

class ParsingError : public exception {
public:
	ParsingError(const string& message);
	ParsingError(const string& message, size_t line);
	virtual const char* what() const noexcept;
private:
	const string message;
	const size_t line;
	string fullErrorMessage;
};
#endif // EXCEPTIONS_HPP