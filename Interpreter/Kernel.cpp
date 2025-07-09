#include "Kernel.h"
#include "Token.h"
#include "LineParser.h"
#include "iostream"
#include <vector>
#include <typeinfo>

Kernel::Kernel()
{
}

KernelState Kernel::interpret(std::string line)
{
    LineParser parser;
    std::vector<Token*>* tokens = parser.parse("defvar 1234+234.3 () *'sdf doifu234'*asdf2");
    for (Token* token : *tokens) {
        
        std::cout << typeid(*token).name() << std::endl;
        std::cout << token->getAlias() << std::endl;
        std::cout << std::endl;
    }
    return KernelState::BREAK;
}
