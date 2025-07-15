#include "Memory.h"
#include "MessageException.h"

Memory::~Memory()
{
	for (std::pair<std::string, DataToken*> data : variable_table) {
		delete data.second;
	}

	for (std::pair<std::string, Function*> data : function_table) {
		delete data.second;
	}
}

void Memory::save(std::string name, DataToken* data)
{
	if (variable_table.contains(name)) {
		delete variable_table[name];
	}
	variable_table[name] = data;
	data = nullptr;
}

void Memory::save(std::string name, Function* data)
{
	if (variable_table.contains(name)) {
		delete variable_table[name];
	}
	function_table[name] = data;
	data = nullptr;
}

DataToken* Memory::loadVariable(std::string name)
{
	if (variable_table.contains(name)) {
		return variable_table[name];
	}
	else {
		throw MessageException("The variable could not be found in memory");
	}
}

Function* Memory::loadFunction(std::string name)
{
	if (function_table.contains(name)) {
		return function_table[name];
	}
	else {
		throw MessageException("The variable could not be found in memory");
	}
}
