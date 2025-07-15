#include "LineParser.h"
#include "MessageException.h"
#include "TokensHeaders.h"
#include <stdexcept>

std::vector<Token*>* LineParser::parse(const std::string& line)
{
	begin = 0;
	this->line = &line;
	std::vector<Token*>* tokens = new std::vector<Token*>();

	while (begin < line.length()) {
		if (line.at(begin) == ' ') {
			begin++;
			continue;
		}
		tokens->push_back(initToken());
	}
	return tokens;
}

Token* LineParser::initToken() {
	// Step 1. Key words and base operators
	if (isPrefix("+")) {
		return new SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"+",
			1,
			[](DataToken& l, DataToken& r) {
				return l + r;
			}
		);
	}
	if (isPrefix("-")) {
		// It can create an OperatorToken and interpret dependencies based on position later
		return new SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"-",
			1,
			[](DataToken& l, DataToken& r) {
				return l - r;
			}
		);
	}
	if (isPrefix("*")) {
		return new SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"*",
			2,
			[](DataToken& l, DataToken& r) {
				return l * r;
			}
		);
	}
	if (isPrefix("/")) {
		return new SymbolBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"/",
			2,
			[](DataToken& l, DataToken& r) {
				return l / r;
			}
		);
	}
	if (isPrefix("pow")) {
		return new NameBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"pow",
			0,
			[](DataToken& l, DataToken& r) {
				return l.pow(r);
			}
		);
	}
	if (isPrefix("abs")) {
		return new UnaryOperatorToken<DataToken*, DataToken&>(
			"abs",
			0,
			[](DataToken& l) {
				return l.abs();
			}
		);
	}
	if (isPrefix("max")) {
		return new NameBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"max",
			0,
			[](DataToken& l, DataToken& r) {
				return l.max(r);
			}
		);
	}
	if (isPrefix("min")) {
		return new NameBinaryOperatorToken<DataToken*, DataToken&, DataToken&>(
			"min",
			0,
			[](DataToken& l, DataToken& r) {
				return l.min(r);
			}
		);
	}
	if (isPrefix("var")) {
		return new IdentifierToken("var", IdentifierToken::type::VAR);
	}
	if (isPrefix("def")) {
		return new IdentifierToken("def", IdentifierToken::type::DEF);
	}
	if (isPrefix("=")) {
		return new Token{
			"=",
			0
		};
	}
	if (isPrefix("(")) {
		return new LeftBracketToken("(", 0);
	}
	if (isPrefix(")")) {
		return new RightBracketToken(")", 0);
	}
	if (isPrefix("{")) {
		return new LeftBracketToken("{", 0);
	}
	if (isPrefix("}")) {
		return new RightBracketToken("}", 0);
	}
	if (isPrefix(",")) {
		return new SeparateToken(",", 0);
	}

	// Step 2. Data types and variables

	status_mode mode = status_mode::START;
	std::string str_token;

	for (size_t i = begin; i <= line->length(); i++) {
		char symbol = ' ';
		if(i != line->length())
			symbol = line->at(i);

		switch (mode)
		{
		case status_mode::LETTER:
			if (isLetter(symbol) || isNumber(symbol)) {
				break;
			}
			return new NameToken(str_token, 0);
		case status_mode::INTEGER:
			if (isNumber(symbol))
				break;
			if (symbol == '.') {
				mode = status_mode::FLOAT;
				break;
			}
			try {
				int value = std::stoi(str_token);
				return new IntegerNumberToken(str_token, value);
			}
			catch (const std::invalid_argument& e) {
				throw MessageException("Integer couldn't have converted to int: " + str_token + ". " + e.what());
			}
			catch (const std::out_of_range& e) {
				throw MessageException("Integer " + str_token + " is large");
			}
		case status_mode::FLOAT:
			if (isNumber(symbol))
				break;
			try {
				float value = std::stof(str_token);
				return new FloatNumberToken(str_token, value);
			}
			catch (const std::invalid_argument& e) {
				throw MessageException("Number with float couldn't have converted to int: " + str_token + ". " + e.what());
			}
			catch (const std::out_of_range& e) {
				throw MessageException("Float " + str_token + " is large");
			}
		case status_mode::START:
			if (isLetter(symbol))
				mode = status_mode::LETTER;
			else if (isNumber(symbol))
				mode = status_mode::INTEGER;
			else if (symbol == '\'')
				mode = status_mode::STRING;
			else
				throw MessageException("Not valid symbol in begin of the token");
			break;
		case status_mode::STRING:
			if (symbol == '\'') {
				begin++;
				return new StringToken(str_token.substr(1));
			}
			break;
		}

		str_token += symbol;
		begin = i + 1;
	}

	throw std::exception("Token is not valid");
}

bool LineParser::isPrefix(const std::string&& prefix)
{
	if (line->substr(begin, prefix.length()) == prefix) {
		begin += prefix.length();
		return true;
	}
	return false;
}

bool LineParser::isNumber(const char symbol)
{
	for (const char number : NUMBERS) {
		if (number == symbol)
			return true;
	}
	return false;
}

bool LineParser::isLetter(const char symbol)
{
	for (const char letter : LETTERS) {
		if (letter == symbol)
			return true;
	}
	return false;
}