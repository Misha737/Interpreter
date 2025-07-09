#pragma once

#include <string>
#include "Token.h"

class LeftBracketToken : public Token {
public:
	LeftBracketToken(std::string alias, size_t priority) : Token(alias, priority) {};
};