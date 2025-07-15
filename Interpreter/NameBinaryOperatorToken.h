#pragma once

#include "BinaryOperatorToken.h"

template<typename E, typename L, typename R>
class NameBinaryOperatorToken : public BinaryOperatorToken<E, L, R> {
private:
	typedef std::function<E(L, R)> binary_evaluation;
public:
	NameBinaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation) :
		BinaryOperatorToken<E, L, R>(alias, priority, evaluation) {}
	Token* copy() const override { return new NameBinaryOperatorToken<E, L, R>(this->alias, this->priority, this->evaluation); };
};