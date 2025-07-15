#pragma once

#include <string>
#include "Token.h"

class SeparateToken : public Token {
public:
	SeparateToken(std::string alias, size_t priority) : Token(alias, priority) {};
	Token* copy() const override { return new SeparateToken(alias, priority); };
};