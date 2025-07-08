#pragma once

#include <string>
#include "Token.h"

class SeparateToken : public Token<std::string> {
public:
	SeparateToken(std::string alias, size_t priority) : Token(alias, priority) {};
};