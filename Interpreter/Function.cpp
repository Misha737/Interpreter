#include "Function.h"
#include "MessageException.h"
#include "Expression.h"

void Function::deleteParameters()
{
	for (Expression* token : parameters) {
		delete token;
	}
	parameters.clear();
}

Function::Function(std::string name, std::vector<NameToken*> parameters, Expression* body)
	: name(name), body(body)
{
	body->bindParameters(parameters);
	number_of_parameters = parameters.size();
}

Function::Function(std::string name, size_t number_of_parameters, Expression* body)
	:name(name), body(body)
{
	this->number_of_parameters = number_of_parameters;

}

Function::~Function()
{
	//delete body;
	deleteParameters();
}

size_t Function::getNumberOfParameters() const
{
	return number_of_parameters;
}

void Function::setCallParameters(std::vector<Expression*>& parameters)
{
	if (parameters.size() != number_of_parameters) {
		throw MessageException("Parameter count mismatch"); 
	}
	if (!this->parameters.empty())
		deleteParameters();
	for (Expression* expression : parameters) {
		this->parameters.push_back(expression->copy());
	}
}

std::vector<Expression*> Function::getParameters()
{
	return parameters;
}

DataToken* Function::evaluate(std::vector<Expression*> parameters, Memory* memory) const
{
	return body->evaluate(memory, &parameters);
}

DataToken* Function::evaluate(Memory* memory) const
{
	return evaluate(this->parameters, memory);
}

Function* Function::copy() const
{
	return new Function(name, number_of_parameters, body);
}
