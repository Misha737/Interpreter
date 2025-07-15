#pragma once

#include <vector>
#include "OperatorToken.h"
#include "Function.h"

class FunctionToken : public OperatorToken {
public:
	Function* function;
	FunctionToken(Function* function) : OperatorToken("", 0), function(function) {}
	Token* copy() const override { return new FunctionToken(new Function(*function)); };
};