#pragma once

#include "Token.h"

class DataToken : public Token {
public:
	DataToken(std::string alias) : Token(alias, 0) {};
	DataToken(const DataToken& other) : Token(other) {};
	virtual DataToken* operator+(DataToken& other) const = 0;
	virtual DataToken* operator-(DataToken& other) const = 0;
	virtual DataToken* operator*(DataToken& other) const = 0;
	virtual DataToken* operator/(DataToken& other) const = 0;
	virtual DataToken* pow(DataToken& pow) const = 0;
	virtual DataToken* abs() const = 0;
	virtual DataToken* max(DataToken& other) const = 0;
	virtual DataToken* min(DataToken& other) const = 0;
	Token* copy() const override = 0;
};