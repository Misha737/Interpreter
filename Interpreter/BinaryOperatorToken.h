#pragma once

#include <functional>
#include "OperatorToken.h"


template<typename E, typename L, typename R>
class BinaryOperatorToken : public OperatorToken {
private:
	typedef std::function<E(L, R)> binary_evaluation;
	binary_evaluation evaluation;
public:
	BinaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation);
	E evaluate(L left_operand, R right_operand) const;
};

template<typename E, typename L, typename R>
BinaryOperatorToken<E, L, R>::BinaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation)
: evaluation(evaluation), OperatorToken(alias, priority) {}

template<typename E, typename L, typename R>
E BinaryOperatorToken<E, L, R>::evaluate(L left_operand, R right_operand) const
{
	return evaluation(left_operand, right_operand);
}
