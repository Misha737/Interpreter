#include "Token.h"

Token::Token(const Token& other)
{
	alias = other.alias;
	priority = other.priority;
}
