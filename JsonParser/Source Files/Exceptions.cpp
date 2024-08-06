#include "./../Header Files/Exceptions.hpp"

ReceiverException::ReceiverException(const string& message) : message(message) {
	fullErrorMessage = "Receiver exception: " + message;
}
ReceiverException::ReceiverException(const string& message, const std::exception& e) : message(message), nestedException(e.what()) {
	fullErrorMessage = message + e.what();
}
const char* ReceiverException::what() const noexcept {
	return fullErrorMessage.c_str();
}


InvokerException::InvokerException(const string& message) : message(message){ }
const char* InvokerException::what() const noexcept {
	return message.c_str();
}


CommandException::CommandException(const string& message) : message(message) {

}
const char* CommandException::what() const noexcept {
	
	return message.c_str();
}


ParsingError::ParsingError(const string& message) : message(message), line(std::string::npos) {
	fullErrorMessage += message;
}
ParsingError::ParsingError(const string& message, size_t line) : message(message), line(line) {
	fullErrorMessage += "Invalid JSON format. " + message + " Line: " + std::to_string(line) + ".";
}
const char* ParsingError::what() const noexcept {
	return fullErrorMessage.c_str();
}