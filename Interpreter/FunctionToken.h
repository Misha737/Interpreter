#pragma once

#include <map>
#include "OperatorToken.h"

class FunctionToken : public OperatorToken {
private:
	void* return_value;
	std::map<std::string, void*> parameters;
public:
	FunctionToken(std::string alias, size_t priority,
		void* return_value, std::map<std::string, void*> parameters)
		: OperatorToken(alias, priority), return_value(return_value), parameters(parameters) {};
};