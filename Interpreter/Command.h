#pragma once

#include <vector>
#include "Token.h"
#include "TokensHeaders.h"
#include "Memory.h"

class Command {
private:
	void parseFunction();
	void parseVariable();
	std::vector<NameToken*> parseDefParameters();
	ExpressionToken* parseExpression(Token* end);
	ExpressionToken* parseFunctionBody();
	std::vector<ExpressionToken*> parseCallParameters(size_t parameters);
	std::vector<Token*> command;
	size_t index = 0;
	Memory* memory;
public:
	Command(Memory* memory) : memory(memory) {}
	void process(std::vector<Token*> command);
};