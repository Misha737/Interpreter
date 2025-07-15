#include <iostream>
#include "Kernel.h"

void main() {
	std::string input_line;
	Kernel kernel;
	bool is_break = false;
	while (true) {
		std::getline(std::cin, input_line);
		switch (kernel.interpret(input_line)) {
		//case KernelState::OK:
		//	break;
		case KernelState::BREAK:
			break;
		}
		if (is_break)
			break;
	}
}