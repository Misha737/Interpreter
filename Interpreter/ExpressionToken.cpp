#include "ExpressionToken.h"

ExpressionToken::~ExpressionToken()
{
	delete expression;
}
