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


int main() {
	MSG("Compiling");
	ScannerClass * scanner = new ScannerClass("test.txt");


	TokenClass tokenClass = scanner->GetNextToken();
	std::cout << scanner->getLineNumber() << ": " << tokenClass << std::endl;
	while (tokenClass.GetTokenType() != TokenType::ENDFILE_TOKEN) {
		tokenClass = scanner->GetNextToken();
		std::cout << scanner->getLineNumber() << ": " << tokenClass << std::endl;
	}

	//StatementNode *statementNode = new StatementNode();
	//StatementGroupNode *statementGroupNode = new StatementGroupNode();
	//BlockNode *blockNode = new BlockNode(statementGroupNode);
	//ProgramNode *programNode = new ProgramNode(blockNode);
	//StartNode* startNode = new StartNode(programNode);
	//delete startNode;
	SymbolTableClass * SymbolTable = new SymbolTableClass();
	ParserClass * Parser = new ParserClass(scanner, SymbolTable);
	Parser->Start();


	//TokenType tt = VOID_TOKEN;
	//std::string lexeme = "void";
	//TokenClass tok1(tt, lexeme);
	//std::cout << tok1 << std::endl;
}