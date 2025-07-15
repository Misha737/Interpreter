#pragma once

#include <string>
#include "DataToken.h"

class StringToken : public DataToken {
public:
	StringToken(std::string alias) : DataToken(alias) {};
	StringToken(const StringToken&);
	DataToken* operator+(DataToken& other) const override;
	DataToken* operator-(DataToken& other) const override;
	DataToken* operator*(DataToken& other) const override;
	DataToken* operator/(DataToken& other) const override;
	DataToken* pow(DataToken& pow) const override;
	DataToken* abs() const override;
	DataToken* max(DataToken& other) const override;
	DataToken* min(DataToken& other) const override;
	Token* copy() const override { return new StringToken(alias); };
};