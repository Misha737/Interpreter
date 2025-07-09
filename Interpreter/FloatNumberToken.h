#pragma once

#include "DataToken.h"

class FloatNumberToken : public DataToken {
	const float value;
public:
	FloatNumberToken(std::string alias, float value)
		: DataToken(alias), value(value) {};
	const float getValue() const { return value; }
	DataToken* operator+(DataToken& other) const override;
	DataToken* operator-(DataToken& other) const override;
	DataToken* operator*(DataToken& other) const override;
	DataToken* operator/(DataToken& other) const override;
	DataToken* pow(DataToken& pow) const override;
	DataToken* abs() const override;
	DataToken* max(DataToken& other) const override;
	DataToken* min(DataToken& other) const override;
};