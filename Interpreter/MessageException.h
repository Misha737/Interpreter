#pragma once

#include <exception>
#include <string>

class MessageException : public std::exception {
private:
	std::string message;
public:
	MessageException(std::string message) : message(message) {};
	const char* what() const noexcept override {
		return message.c_str();
	}
};