#pragma once

#include <vector>
#include "TokensHeaders.h"

static const std::string NUMBERS = "1234567890";
static const std::string LETTERS = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";

class LineParser {
private:
	const std::string* line;
	size_t begin = 0;
	bool isNumber(const char symbol);
	bool isLetter(const char symbol);
	enum status_mode { START, LETTER, INTEGER, FLOAT, STRING };
	Token* initToken();
	bool isPrefix(const std::string&& prefix);
public:
	std::vector<Token*>* parse(const std::string& line);
};