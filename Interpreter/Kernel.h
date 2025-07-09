#pragma once

#include <string>
#include "Memory.h"

enum KernelState {
	OK, BREAK
};

class Kernel {
private:
	Memory memory;
public:
	Kernel();
	KernelState interpret(std::string line);
};
