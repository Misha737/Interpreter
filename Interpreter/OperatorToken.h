#pragma once

#include "Token.h"
#include <string>

class OperatorToken : public Token<std::string> {
public:
	OperatorToken(std::string alias, size_t priority) : Token<std::string>(alias, priority) {};
};