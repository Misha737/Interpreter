#include "Kernel.h"
#include "Token.h"
#include "iostream"
#include <vector>

Kernel::Kernel() : command(Command(&memory))
{
}

KernelState Kernel::interpret(std::string line)
{
	if (line == "exit")
		return KernelState::BREAK;
	std::vector<Token*>* tokens;
	try {
		tokens = parser.parse(line);
		command.process(*tokens);
		for (Token* token : *tokens) {
			delete token;
		}
		delete tokens;
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;
	}


	return KernelState::OK;
}
