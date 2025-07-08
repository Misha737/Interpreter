#pragma once

#include <string>
#include "Token.h"

class LeftBracketToken : public Token<std::string> {
public:
	LeftBracketToken(std::string alias, size_t priority) : Token(alias, priority) {};
};