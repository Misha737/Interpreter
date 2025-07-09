#pragma once

#include "DataToken.h"

class IntegerNumberToken : public DataToken {
private:
	const int value;
public:
	IntegerNumberToken(std::string alias, int value)
		: DataToken(alias), value(value) {};
	const int getValue() const { return value; };
	DataToken* operator+(DataToken& other) const override;
	DataToken* operator-(DataToken& other) const override;
	DataToken* operator*(DataToken& other) const override;
	DataToken* operator/(DataToken& other) const override;
	DataToken* pow(DataToken& pow) const override;
	DataToken* abs() const override;
	DataToken* max(DataToken& other) const override;
	DataToken* min(DataToken& other) const override;

};