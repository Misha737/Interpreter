#pragma once

#include <string>
#include "Token.h"

class NameToken : public Token {
public:
	NameToken(std::string alias, size_t priority) : Token(alias, priority) {};
	NameToken(const NameToken& other) : Token(other) {};
	Token* copy() const override { return new NameToken(alias, priority); };

};