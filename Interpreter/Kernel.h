#pragma once

#include <string>
#include "Memory.h"
#include "LineParser.h"
#include "Command.h"

enum KernelState {
	OK, BREAK
};

class Kernel {
private:
	LineParser parser;
	Memory memory;
	Command command;

public:
	Kernel();
	KernelState interpret(std::string line);
};
