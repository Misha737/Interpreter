#include "Command.h"
#include <stack>
#include "MessageException.h"
#include "Function.h"
#include <stdexcept>

void Command::parseFunction()
{
	if (NameToken* name = dynamic_cast<NameToken*>(command.at(++index))) {
		if (LeftBracketToken* leftRoundBracket = dynamic_cast<LeftBracketToken*>(command.at(++index))) {
			if (leftRoundBracket->getAlias() == "(") {
				index++;
				std::vector<NameToken*> parameters = parseDefParameters();
				if (LeftBracketToken* leftCurlyBracket = dynamic_cast<LeftBracketToken*>(command.at(++index))) {
					if (leftCurlyBracket->getAlias() == "{") {
						index++;
						RightBracketToken end("}", 0);
						Expression* body = parseExpression(&end)->expression;
						Function* function = new Function(name->getAlias(), parameters, body);
						memory->save(name->getAlias(), function);
						function = nullptr;
						body = nullptr;
						return;
					}
				}
			}
		}
	}
	throw MessageException("Syntax for function definition is not correct");
}

void Command::parseVariable()
{
	if (NameToken* name = dynamic_cast<NameToken*>(command.at(++index))) {
		if (command.at(++index)->getAlias() == "=") {
			index++;
			DataToken* value = parseExpression(nullptr)->expression->evaluate(memory);
			memory->save(name->getAlias(), value);
			value = nullptr;
			return;
		}
	}
	throw MessageException("Syntax for variable is not correct");
}

std::vector<NameToken*> Command::parseDefParameters()
{
	Token* token = command.at(index);
	std::vector<NameToken*> parameters;

	if (NameToken* parameter = dynamic_cast<NameToken*>(token)) {
		parameters.push_back(parameter);
	}
	else {
		index--;
	}
	while (++index < command.size()) {
		token = command.at(index);
		if (RightBracketToken* rightBracket = dynamic_cast<RightBracketToken*>(token)) {
			if (rightBracket->getAlias() == ")") {
				return parameters;
			}
			else {
				throw MessageException("Syntax is not correct. Invalid symbol " + rightBracket->getAlias());
			}
		}

		if (dynamic_cast<SeparateToken*>(token)) {
			if (NameToken* parameter = dynamic_cast<NameToken*>(command.at(++index))) {
				parameters.push_back(parameter);
			}
			else {
				throw MessageException("Syntax is not correct");
			}
		}
		else {
			throw MessageException("Syntax is not correct. Invalid symbol " + token->getAlias());
		}
	}
	throw MessageException("Syntax is not correct. Symbol RightBracketToken doesn't exist");
}

// Повертати індекс, щоб ініцілізувати вираз як підмножина, із діапазонами меж вектора
ExpressionToken* Command::parseExpression(Token* end = nullptr)
{
	std::vector<Token*> expression_tokens;

	enum states { OPERATOR, OPERAND };
	states state = states::OPERAND;
	index--;
	while (++index < command.size()) {
		Token* token = command.at(index);

		switch (state)
		{
		case states::OPERAND:
			if (token->getAlias() == "(") {
				index++;
				RightBracketToken ending = RightBracketToken(")", 0);
				expression_tokens.push_back(parseExpression(&ending));
				state = states::OPERATOR;
			}
			else if (NameToken* name = dynamic_cast<NameToken*>(token)) {
				Token* next_token;
				state = states::OPERATOR;
				try
				{
					next_token = command.at(index + 1);
					if (LeftBracketToken* bracket = dynamic_cast<LeftBracketToken*>(next_token)) {
						if (bracket->getAlias() == "(") {
							index++;
							// name is defined function
							Function* function = memory->loadFunction(name->getAlias());
							std::vector<ExpressionToken*> pars = parseCallParameters(function->getNumberOfParameters());
							std::vector<Expression*> ex_pars;
							for (ExpressionToken* par : pars) {
								ex_pars.push_back(new Expression(*par->expression));
								delete par;
							}
							Function* function_copy = function->copy();
							function_copy->setCallParameters(ex_pars);
							expression_tokens.push_back(new FunctionToken(function_copy));
							function = nullptr;
							function_copy = nullptr;
							continue;
						}
						else {
							throw MessageException("Syntax is not correct");
						}

					}
				}
				catch (const std::out_of_range&)
				{
				}
				expression_tokens.push_back(name);
			}
			else if (NameBinaryOperatorToken<DataToken*, DataToken&, DataToken&>* name =
				dynamic_cast<NameBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(token)) {
				// But if named unary operator
				Token* next_token;
				try {
					next_token = command.at(++index);
					expression_tokens.push_back(name);
					if (dynamic_cast<LeftBracketToken*>(next_token)) {
						if (next_token->getAlias() == "(") {
							expression_tokens.push_back(next_token);
							std::vector<ExpressionToken*> operands = parseCallParameters(2);
							expression_tokens.insert(expression_tokens.end(), operands.begin(), operands.end());
							expression_tokens.push_back(command.at(index));
							state = states::OPERATOR;
						}
						else {
							throw MessageException("Syntax is not correct. Invalid symbol: " + next_token->getAlias());
						}
					}
					else {
						throw MessageException("Syntax is not correct. Invalid symbol: " + next_token->getAlias());
					}
				}
				catch (const std::out_of_range&)
				{
					throw MessageException("Syntax is not correct. Symbol \"(\" is not exist");
				}
			}
			else if (DataToken* data = dynamic_cast<DataToken*>(token)) {
				expression_tokens.push_back(data);
				state = states::OPERATOR;
			}
			else if (end != nullptr) {
				if (token->getAlias() == end->getAlias()) {
					return new ExpressionToken(expression_tokens);
				}
			}
			else {
				if (token != nullptr)
					throw MessageException("Syntax is not correct. " + token->getAlias());
				else
					throw MessageException("Syntax is not correct. ");
			}
			break;
		case states::OPERATOR:
			if (end != nullptr) {
				if (token->getAlias() == end->getAlias()) {
					return new ExpressionToken(expression_tokens);
				}
			}
			if (dynamic_cast<SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(token)) {
				state = states::OPERAND;
				expression_tokens.push_back(token);
				continue;
			}
			else {
				throw MessageException("Syntax is not correct. It has been waited for the symbol operator");
			}
			break;
		}
	}
	if (state == states::OPERATOR) {
		return new ExpressionToken(expression_tokens);
	}
	throw MessageException("Syntax is not correct");
	//switch (state)
	//{
	//case OPERATOR:
	//	break;
	//case OPERAND:
	//	break;
	//}
}

ExpressionToken* Command::parseFunctionBody()
{
	Token* token = command.at(index);
	if (LeftBracketToken* left_token = dynamic_cast<LeftBracketToken*>(token)) {
		if (left_token->getAlias() == "{") {
			RightBracketToken ending = RightBracketToken("}", 0);
			return parseExpression(&ending);
		}
	}
	throw MessageException("Syntax is not correct. Invalid symbol " + token->getAlias());
}

//Expression* Command::createExpression(Token* end = nullptr)
//{
//	size_t start_index = index + 1;
//	parseExpression(end);
//	size_t end_index = index - 1;
//	std::vector<Token*> expression;
//	expression.insert(expression.end(), command.begin() + start_index, command.begin() + end_index);
//	return new Expression(expression);
//}

std::vector<ExpressionToken*> Command::parseCallParameters(size_t number_of_parameters)
{
	std::vector<ExpressionToken*> parameters;

	try {
		if (number_of_parameters == 0) {
			if (command.at(index + 1)->getAlias() == ")") {
				index++;
				return parameters;
			}
			throw MessageException("Syntax for call parameters are don't correct");
		}
	}
	catch (const std::out_of_range&) {
		throw MessageException("Syntax for call parameters are don't correct");
	}

	//index--;
	while (++index < command.size() && parameters.size() <= number_of_parameters) {
		if (number_of_parameters - 1 == parameters.size()) {
			RightBracketToken end = RightBracketToken(")", 0);
			parameters.push_back(parseExpression(&end));
			return parameters;
		}
		else {
			SeparateToken separator = SeparateToken(",", 0);
			parameters.push_back(parseExpression(&separator));
		}
	}
	throw MessageException("Syntax for call parameters are don't correct");
}

#include <iostream>

void Command::process(std::vector<Token*> command)
{
	this->command = command;
	index = 0;
	Token* token = command.at(0);
	if (IdentifierToken* identifier = dynamic_cast<IdentifierToken*>(token)) {
		switch (identifier->getIdentifier())
		{
		case IdentifierToken::type::DEF:
			parseFunction();
			break;
		case IdentifierToken::type::VAR:
			parseVariable();
			break;
		}
	}
	else {
		ExpressionToken* expression = parseExpression();
		std::cout << expression->expression->evaluate(memory)->getAlias() << std::endl;
		delete expression;
	}
	//throw MessageException("Syntax is not correct");
}
