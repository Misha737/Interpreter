#include "Expression.h"
#include <stack>
#include "TokensHeaders.h"
#include "MessageException.h"

Expression::Expression(std::vector<Token*> infix)
{
	for (Token* token : infix) {
		tokens.push_back(token->copy());
	}
	toPostfix();
}

Expression::Expression(const Expression& other)
{
	for (const Token* token : other.tokens) {
		tokens.push_back(token->copy());
	}
}

Expression::~Expression()
{
	for (Token* token : tokens) {
		delete token;
	}
}

void Expression::toPostfix()
{
	std::vector<Token*> postfix;
	std::stack<Token*> stack;
	for (Token* token : tokens) {
		if (DataToken* data = dynamic_cast<DataToken*>(token)) {
			postfix.push_back(data);
		}
		else if (ExpressionToken* expression = dynamic_cast<ExpressionToken*>(token)) {
			postfix.push_back(expression);
		}
		else if (FunctionToken* function = dynamic_cast<FunctionToken*>(token)) {
			postfix.push_back(function);
		}
		else if (NameToken* name = dynamic_cast<NameToken*>(token)) {
			postfix.push_back(name);
		}
		else if (dynamic_cast<LeftBracketToken*>(token)) {
			stack.push(token);
		}
		else if (dynamic_cast<NameBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(token)) {
			stack.push(token);
		}
		else if (dynamic_cast<UnaryOperatorToken<DataToken*, DataToken&>*>(token)) {
			stack.push(token);
		}
		else if (dynamic_cast<RightBracketToken*>(token)) {
			bool found = false;
			while (!stack.empty()) {
				LeftBracketToken* left = dynamic_cast<LeftBracketToken*>(stack.top());
				if (left == nullptr) {
					postfix.push_back(stack.top());
					stack.pop();
				}
				else {
					stack.pop();
					found = true;
					break;
				}
			}
			if (!found) {
				throw MessageException("No left bracket found in the expression");
			}
			postfix.push_back(stack.top());
			stack.pop();
		}
		else if (auto bin_operator = dynamic_cast<SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(token)) {
			if (!stack.empty()) {
				auto s_bin_operator =
					dynamic_cast<SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(stack.top());
				while (s_bin_operator && bin_operator->getPriority() <= s_bin_operator->getPriority()) {
					postfix.push_back(s_bin_operator);
					stack.pop();
					if (stack.empty())
						break;
					s_bin_operator =
						dynamic_cast<SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(stack.top());
				}
			}
			stack.push(bin_operator);
		}
		else {
			throw MessageException("Unknown token");
		}
	}

	while (!stack.empty()) {
		postfix.push_back(stack.top());
		stack.pop();
	}

	tokens.clear();
	tokens = postfix;
}

DataToken* Expression::evaluate(Memory* memory) const
{
	return evaluate(memory, nullptr);
}

DataToken* Expression::evaluate(Memory* memory, std::vector<Expression*>* env = nullptr) const
{
	std::stack<DataToken*> stack;
	for (Token* token : tokens) {
		if (VariableNameToken* variable = dynamic_cast<VariableNameToken*>(token)) {
			stack.push(memory->loadVariable(variable->getAlias()));
		}
		else if (ParameterNameToken* variable = dynamic_cast<ParameterNameToken*>(token)) {
			if (env == nullptr)
				throw MessageException("Parameter is not valid");
			stack.push(env->at(variable->getIndex())->evaluate(memory, env));
		}
		else if (NameToken* variable = dynamic_cast<NameToken*>(token)) {
			stack.push(memory->loadVariable(variable->getAlias()));
		}
		else if (ExpressionToken* expression = dynamic_cast<ExpressionToken*>(token)) {
			stack.push(expression->expression->evaluate(memory, env));
		}
		else if (DataToken* data = dynamic_cast<DataToken*>(token)) {
			stack.push(dynamic_cast<DataToken*>(data->copy()));
		}
		else if (FunctionToken* function = dynamic_cast<FunctionToken*>(token)) {
			std::vector<Expression*> pars = function->function->getParameters();
			for (Expression* expression : pars) {
				std::vector<Token*>* tokens = expression->getTokens();
				for (size_t i = 0; i < tokens->size(); i++) {
					if (ParameterNameToken* par = dynamic_cast<ParameterNameToken*>(tokens->at(i))) {
						Token* temp = env->at(par->getIndex())->evaluate(memory, env);
						delete tokens->at(i);
						tokens->at(i) = temp;
					}
				}
			}
			stack.push(function->function->evaluate(memory));
		}
		else if (BinaryOperatorToken<DataToken*, DataToken&, DataToken&>* op =
			dynamic_cast<BinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(token)) {
			DataToken* operand1 = stack.top();
			stack.pop();
			DataToken* operand2 = stack.top();
			stack.pop();
			stack.push(op->evaluate(*operand2, *operand1));
			delete operand1;
			delete operand2;
		}
		//else if (SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>* op =
		//	dynamic_cast<SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>*>(token)) {
		//	DataToken* operand1 = stack.top();
		//	stack.pop();
		//	DataToken* operand2 = stack.top();
		//	stack.pop();
		//	stack.push(op->evaluate(*operand1, *operand2));
		//	delete operand1;
		//	delete operand2;
		//}
		else {
			throw MessageException("Unknown token");
		}
	}
	return stack.top();

}

void Expression::bindParameters(const std::vector<NameToken*>& parameters)
{
	for (size_t i = 0; i < tokens.size(); i++) {
		if (NameToken* name = dynamic_cast<NameToken*>(tokens[i])) {
			Token* temp_token = new VariableNameToken(name->getAlias());
			delete tokens[i];
			tokens[i] = temp_token;
			for (size_t j = 0; j < parameters.size(); j++) {
				if (tokens[i]->getAlias() == parameters[j]->getAlias()) {
					temp_token = new ParameterNameToken(
						tokens[i]->getAlias(),
						tokens[i]->getPriority(),
						j);
					delete tokens[i];
					tokens[i] = temp_token;
					break;
				}
			}
		}
		else if (FunctionToken* function = dynamic_cast<FunctionToken*>(tokens[i])) {
			for (Expression* expression : function->function->getParameters()) {
				expression->bindParameters(parameters);
			}
		}
		else if (ExpressionToken* expression = dynamic_cast<ExpressionToken*>(tokens[i])) {
			expression->expression->bindParameters(parameters);
		}
	}
}

Expression* Expression::copy() const
{
	return new Expression(*this);
}
