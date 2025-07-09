#pragma once

#include "DataToken.h"
#include <vector>

class Expression {
private:
	std::vector<const Token*> expression;
public:
	Expression(std::vector<const Token*> infix);
	void toPostfix();
	DataToken* evaluate() const;
};