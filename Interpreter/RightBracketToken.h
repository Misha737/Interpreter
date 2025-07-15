#pragma once

#include <string>
#include "Token.h"

class RightBracketToken : public Token{
public:
	RightBracketToken(std::string alias, size_t priority) : Token(alias, priority) {};
	Token* copy() const override { return new RightBracketToken(alias, priority); };
};