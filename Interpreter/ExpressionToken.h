#pragma once

#include "Token.h"
#include "Expression.h"

class ExpressionToken : public Token {
public:
	Expression* expression;
	ExpressionToken(Expression* expression) : Token("", 0), expression(expression) {};
	~ExpressionToken();
	ExpressionToken(std::vector<Token*>& expression) : Token("", 0), expression(new Expression(expression)) {};
	Token* copy() const override { return new ExpressionToken(new Expression(*expression)); };
};