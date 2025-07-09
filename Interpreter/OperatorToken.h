#pragma once

#include "Token.h"
#include <string>

class OperatorToken : public Token {
public:
	OperatorToken(std::string alias, size_t priority) : Token(alias, priority) {};
};