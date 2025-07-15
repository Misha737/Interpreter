#pragma once
#include "NameToken.h"
#include "DataToken.h"

class VariableNameToken : public NameToken {
public:
	VariableNameToken(std::string name) : NameToken(name, 0) {};
	VariableNameToken(const VariableNameToken& other) : NameToken(other) {}
	Token* copy() const override { return new VariableNameToken(alias); }
};