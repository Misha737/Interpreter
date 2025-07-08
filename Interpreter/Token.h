#pragma once


template<typename T>
class Token {
protected:
	T alias;
	size_t priority;
public:
	Token(T alias, size_t priority) : alias(alias), priority(priority) {};
	const T getAlias() const { return alias; }
	const size_t getPriority() const { return priority; };
};