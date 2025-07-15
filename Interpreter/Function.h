#pragma once

#include <vector>
#include "DataToken.h"
#include "NameToken.h"
//#include "Expression.h"

class Memory;
class Expression;

class Function {
private:
	Expression* body;
	std::string name;
	size_t number_of_parameters;
	std::vector<Expression*> parameters;
	void deleteParameters();
public:
	Function(std::string name, std::vector<NameToken*> parameters, Expression* body);
	Function(std::string name, size_t number_of_parameters, Expression* body);
	~Function();
	size_t getNumberOfParameters() const;
	void setCallParameters(std::vector<Expression*>& parameters);
	std::vector<Expression*> getParameters();
	DataToken* evaluate(std::vector<Expression*> parameters, Memory* memory) const;
	DataToken* evaluate(Memory* memory) const;
	Function* copy() const;
};