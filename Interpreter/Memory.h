#pragma once

#include <map>
#include "Function.h"
#include "DataToken.h"

class Memory {
private:
	std::map<std::string, DataToken*> variable_table;
	std::map<std::string, Function*> function_table;
public:
	Memory() {};
	~Memory();
	void save(std::string name, DataToken* data);
	void save(std::string name, Function* data);
	DataToken* loadVariable(std::string name);
	Function* loadFunction(std::string name);
};