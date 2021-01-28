#include "Token.h"

#include <string>
#include <iostream>

int main() {
	TokenType tt = VOID_TOKEN;
	std::string lexeme = "void";
	TokenClass tok1(tt, lexeme);
	std::cout << tok1 << std::endl;
}