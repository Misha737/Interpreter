#pragma once

#include "Token.h"

class IdentifierToken : public Token {
public:
	static enum type {
		VAR, DEF
	};
	IdentifierToken(std::string alias, type identifier) : Token(alias, 0), identifier(identifier) {}
	type getIdentifier() const { return identifier; }
private:
	type identifier;
};