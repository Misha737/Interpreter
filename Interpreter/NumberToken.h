#pragma once

#include "DataToken.h"

template<typename T>
class NumberToken : public DataToken<T> {
public:
	NumberToken(T alias, size_t priority) : DataToken<T>(alias, priority) {};
};