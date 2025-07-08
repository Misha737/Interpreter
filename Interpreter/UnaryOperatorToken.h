#pragma once

#include <functional>
#include "OperatorToken.h"


template<typename E, typename P>
class BinaryOperatorToken : public OperatorToken {
private:
	typedef std::function<E(P)> binary_evaluation;
	binary_evaluation evaluation;
public:
	BinaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation);
	E evaluate(P left_operand) const;
};

template<typename E, typename P>
BinaryOperatorToken<E, P>::BinaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation)
	: evaluation(evaluation), OperatorToken(alias, priority) {
}

template<typename E, typename P>
E BinaryOperatorToken<E, P>::evaluate(P left_operand) const
{
	return evaluation(left_operand, right_operand);
}
