#pragma once

#include <string>
#include "DataToken.h"

class StringToken : public DataToken<std::string> {
public:
	StringToken(std::string alias, size_t priority) : DataToken<std::string>(alias, priority) {};
};