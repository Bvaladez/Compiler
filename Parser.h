#pragma once

#include "Scanner.h"
#include "Symbol.h"
#include "Node.h"

class ParserClass {

public:

	ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable);
	~ParserClass();

	StartNode * Start();
	ProgramNode * Program();
	BlockNode * Block();
	StatementGroupNode * StatementGroup();
	StatementNode * Statement();
	DeclarationStatementNode * DeclarationStatement();
	AssignmentStatementNode * AssignmentStatement();
	CoutStatementNode * CoutStatement();
	void Expression();
	void Relational();
	void PlusMinus();
	void TimesDivide();
	void Factor();
	void Integer();
	void Identifier();

	TokenClass Match(TokenType expectedType);

private:
	ScannerClass* mScanner;
	SymbolTableClass* mSymbolTable;

};