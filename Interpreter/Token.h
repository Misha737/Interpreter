#pragma once


#include <string>

class Token {
protected:
	std::string alias;
	size_t priority;
public:
	Token(std::string alias, size_t priority) : alias(alias), priority(priority) {};
	virtual const std::string getAlias() const { return alias; }
	const size_t getPriority() const { return priority; };
};