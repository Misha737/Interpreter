#pragma once

#include "Token.h"
#include "BinaryOperatorToken.h"
#include "exception"


class TokenInit {
private:

public:
	//TokenInit();
	template<typename E, typename L, typename R>
	static Token* toToken(std::string key);
};

template<typename E, typename L, typename R>
inline Token* TokenInit::toToken(std::string key)
{
	if (key == "+") {
		return new BinaryOperatorToken<E, L, R>(
			[](L l, R r) {return l + r;},
			"+",
			0
		);
	}
	//else if {

	//}
	throw std::exception("Token is not valid");
}
