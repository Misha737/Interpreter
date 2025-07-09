#pragma once

#include <map>

class Memory {
private:
	std::map<std::string, void*>* memory_table;
};