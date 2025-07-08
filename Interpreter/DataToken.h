#pragma once

#include "Token.h"

template<typename T>
class DataToken : public Token<T> {
public:
	DataToken(T alias, size_t priority) : Token<T>(alias, priority) {};
};