#pragma once

#include "NumberToken.h"

class FloatNumberToken : public NumberToken<float> {
public:
	FloatNumberToken(float alias, size_t priority) : NumberToken(alias, priority) {};
};