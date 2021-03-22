#pragma once

#include "Scanner.h"
#include "Symbol.h"


class ParserClass {

public:

	ParserClass(ScannerClass *Scanner, SymbolTableClass *SymbolTable);
	~ParserClass();

	void Start();
	void Program();
	void Block();
	void StatementGroup();
	bool Statement();
	void DeclarationStatement();
	void AssignmentStatement();
	void CoutStatement();
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