#pragma once

#include "NumberToken.h"

class IntegerNumberToken : public NumberToken<int> {
public:
	IntegerNumberToken(int alias, size_t priority) : NumberToken<int>(alias, priority) {};
};