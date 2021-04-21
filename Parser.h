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
	StatementNode * AssignmentStatement();
	IfStatementNode* IfStatement();
	WhileStatementNode * WhileStatement();
	CoutStatementNode * CoutStatement();
	ExpressionNode * Expression();
	ExpressionNode * Relational();
	ExpressionNode * BitwiseAndStatement();
	ExpressionNode * BitwiseOrStatement();
	ExpressionNode * AndStatement();
	ExpressionNode * OrStatement();
	ExpressionNode * PlusMinus();
	ExpressionNode * TimesDivide();
	ExpressionNode * Exponent();
	ExpressionNode * Factor();
	IntegerNode * Integer();
	IdentifierNode * Identifier();

	TokenClass Match(TokenType expectedType);

private:
	ScannerClass* mScanner;
	SymbolTableClass* mSymbolTable;

};