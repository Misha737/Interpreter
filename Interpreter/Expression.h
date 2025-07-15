#pragma once

#include "DataToken.h"
#include "NameToken.h"
#include "Memory.h"
#include <vector>

class Expression {
private:
	std::vector<Token*> tokens;
	void toPostfix();
public:
	Expression(std::vector<Token*> infix);
	Expression(const Expression&);
	~Expression();
	DataToken* evaluate(Memory* memory) const;
	DataToken* evaluate(Memory* memory, std::vector<Expression*>* env) const;
	Token* operator[](size_t index) { return tokens.at(index); }
	void bindParameters(const std::vector<NameToken*>& parameters);
	Expression* copy() const;
	std::vector<Token*>* getTokens() { return &tokens; }
};