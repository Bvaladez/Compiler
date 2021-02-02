#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Token.h"

#include <string>
#include <iostream>

int main() {
	ScannerClass scanner("test.txt");


	TokenClass tokenClass = scanner.GetNextToken();
	std::cout << tokenClass << std::endl;
	while (tokenClass.GetTokenType() != TokenType::ENDFILE_TOKEN) {
		tokenClass = scanner.GetNextToken();
		std::cout << tokenClass << std::endl;
	}

	//TokenType tt = VOID_TOKEN;
	//std::string lexeme = "void";
	//TokenClass tok1(tt, lexeme);
	//std::cout << tok1 << std::endl;
}