#pragma once

#include "NameToken.h"

class ParameterNameToken : public NameToken {
private:
	size_t index;
public:
	ParameterNameToken(const NameToken& name, size_t index) :
		NameToken(name.getAlias(), name.getPriority()), index(index) {}
	ParameterNameToken(std::string alias, size_t priority, size_t index) :
		NameToken(alias, priority), index(index) {}
	ParameterNameToken(const ParameterNameToken& other) : NameToken(other), index(other.index) {};
	size_t getIndex() const { return index; }
	Token* copy() const override { return new ParameterNameToken(alias, priority, index); };
};