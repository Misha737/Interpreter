#pragma once

#include <functional>
#include "OperatorToken.h"


template<typename E, typename P>
class UnaryOperatorToken : public OperatorToken {
private:
	typedef std::function<E(P)> binary_evaluation;
	binary_evaluation evaluation;
public:
	UnaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation);
	E evaluate(P operand) const;
	Token* copy() const override { return new UnaryOperatorToken(alias, priority, evaluation); };
};

template<typename E, typename P>
inline UnaryOperatorToken<E, P>::UnaryOperatorToken(std::string alias, size_t priority, binary_evaluation evaluation)
	: evaluation(evaluation), OperatorToken(alias, priority) {
}

template<typename E, typename P>
inline E UnaryOperatorToken<E, P>::evaluate(P operand) const
{
	return evaluation(operand);
}
