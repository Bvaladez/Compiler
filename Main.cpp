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

enum {
	interpret, compile
};

void CodeAndExecute(std::string inputFile)
{
	// Create scanner, symbol table, and parser objects.
	ScannerClass scanner(inputFile);
	SymbolTableClass symbolTable;
	ParserClass parser(&scanner, &symbolTable);

	// Do the parsing, which results in a parse tree.
	StartNode* root = parser.Start();

	// Create the machine code instructions from the parse tree
	InstructionsClass machineCode;
	root->Code(machineCode);
	machineCode.Finish();
	if (ShowCode) {
		machineCode.PrintAllMachineCodes();
	}

	// Execute the machine code instructions previously created
	machineCode.Execute();

	// cleanup recursively
	delete root;
}


void Interpret(std::string inputFile) {
	
	// Creat Scanner, Symbol table, and Parser Objects	
	MSG("Interpreting");
	ScannerClass Scanner(inputFile);
	SymbolTableClass SymbolTable;
	ParserClass Parser(&Scanner, &SymbolTable);

	
	// do the parsing creating a parse tree
	StartNode* root = Parser.Start();
	root->Interpret();
	delete root;
}

int main() {
	//Interpret("testPE.txt");
	CodeAndExecute("testCoding.txt");
}

