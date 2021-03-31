#include "Token.h"
#include "Scanner.h"
#include "StateMachine.h"
#include "Token.h"
#include "debug.h"
#include "Symbol.h"
#include "Node.h"
#include "Parser.h"

#include <iomanip>
#include <string>
#include <iostream>

//void Interpret(String inputFile) {
//	ScannerClass(inputFile);
//	SymbolTableClass symbolTable;
//	ParserClass parser(&scanner, &symbolTable);
//
//	StartNode* root = parser.Start();
//
//	root->Interpret();
//
//	delete root;
//}
void Interpret(std::string inputFile) {
	MSG("Interpreting");
	ScannerClass Scanner(inputFile);
	SymbolTableClass SymbolTable;
	ParserClass Parser(&Scanner, &SymbolTable);

	StartNode* root = Parser.Start();
	root->Interpret();
	delete root;
}

int main() {
	Interpret("test.txt");
}

