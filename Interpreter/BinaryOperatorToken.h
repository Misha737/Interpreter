#pragma once

#include <functional>
#include "OperatorToken.h"


template<typename E, typename L, typename R>
class BinaryOperatorToken : public OperatorToken {
protected:
	typedef std::function<E(L, R)> binary_evaluation;
	binary_evaluation evaluation;
public:
	BinaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation)
		: evaluation(evaluation), OperatorToken(alias, priority) {};
	E evaluate(L left_operand, R right_operand) const {
		return evaluation(left_operand, right_operand);
	}
	Token* copy() const override { return new BinaryOperatorToken(alias, priority, evaluation); }
};