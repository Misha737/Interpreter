#pragma once

#include <vector>
#include "OperatorToken.h"
#include "Expression.h"

class FunctionToken : public OperatorToken {
private:
	size_t number_of_parameters;
	const Expression* body = nullptr;
public:
	FunctionToken(std::string alias, size_t priority,
		size_t number_of_parameters, const Expression& body)
		: OperatorToken(alias, priority), number_of_parameters(number_of_parameters) {};
	void setBody(const Expression* body) { this->body = body; }
	DataToken* evaluate(std::vector<DataToken*> parameters) const;
};