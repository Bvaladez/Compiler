#include "Parser.h"
#include "Debug.h"


ParserClass::ParserClass(ScannerClass* Scanner, SymbolTableClass* SymbolTable) {
	mScanner = Scanner;
	mSymbolTable = SymbolTable;
}

StartNode * ParserClass::Start() {
	ProgramNode* pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode* sn = new StartNode(pn);
	return sn;
}

ProgramNode * ParserClass::Program() {
	BlockNode* bn = Block();
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	Block();
	ProgramNode* pn = new ProgramNode(bn);
	return pn;
}

BlockNode * ParserClass::Block() {
	StatementGroupNode* sgn = StatementGroup();
	Match(LCURLY_TOKEN);
	StatementGroup();
	Match(RCURLY_TOKEN);
	BlockNode* bn = new BlockNode(sgn);
	return bn;
}

StatementGroupNode * ParserClass::StatementGroup() {
	StatementGroupNode* sgn = new StatementGroupNode();
	StatementNode * sn;
	do {
		sn = Statement();
		if (sn != NULL) {
			sgn->addStatement(sn);
		}
	}
	while (sn != NULL);
	return sgn;
}

StatementNode * ParserClass::Statement() {

	TokenClass Token = mScanner->PeekNextToken();
	TokenType tt = Token.GetTokenType();
	if (tt == INT_TOKEN) {
		DeclarationStatement();
		StatementNode* sn = new StatementNode();
		return sn;
	}
	else if (tt == IDENTIFIER_TOKEN) {
		AssignmentStatement();
		StatementNode* sn = new StatementNode();
		return sn;
	}
	else if (tt == COUT_TOKEN) {
		CoutStatement();
		StatementNode* sn = new StatementNode();
		return sn;
	}
	else {
		return NULL;
	}

}

ExpressionNode *  ParserClass::Expression() {
	return Relational();
}

ExpressionNode * ParserClass::Relational() {
	ExpressionNode * current = PlusMinus();

	//handle optional tail (LL1 parser)
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN) {
		Match(tt);
		current = new LessNode(current, PlusMinus());
	}
	else if(tt == LESSEQUAL_TOKEN){
		Match(tt);
		current = new LessEqualNode(current, PlusMinus());
	}
	else if (tt == GREATER_TOKEN) {
		Match(tt);
		current = new GreaterNode(current, PlusMinus());
	}
	else if (tt == GREATEREQUAL_TOKEN) {
		Match(tt);
		current = new GreaterEqualNode(current, PlusMinus());
	}
	else if (tt == EQUAL_TOKEN) {
		Match(tt);
		current = new EqualNode(current, PlusMinus());
	}
	else if (tt == NOTEQUAL_TOKEN) {
		Match(tt);
		current = new NotEqualNode(current, PlusMinus());
	}
	else {
		return current;
	}
}

ExpressionNode * ParserClass::PlusMinus() {
	ExpressionNode * current  = TimesDivide();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, TimesDivide());
		}
		else if (tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, TimesDivide());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode * ParserClass::TimesDivide() {
	ExpressionNode * current = Factor();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN) {
			Match(tt);
			current = new TimesNode(current, Factor());
		}
		else if (tt == DIVIDE_TOKEN) {
			Match(tt);
			current = new DivideNode(current, Factor());
		}
		else {
			return current;
		}
	}
}

ExpressionNode * ParserClass::Factor() {
	ExpressionNode* current;
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == IDENTIFIER_TOKEN) {
		current = Identifier();
		return current;
	}
	else if (tt == INTEGER_TOKEN) {
		current = Integer();
		return current;
	}
	else if (tt == LPAREN_TOKEN) {
		current = Expression();
		Match(RPAREN_TOKEN);
		return current;
	}
	else {
		std::cerr << "Unexpected Token --> " << tt << std::endl;
		std::exit(1);
	}
	
}
IdentifierNode * ParserClass::Identifier() {
	TokenClass token = Match(IDENTIFIER_TOKEN);
	std::string label = token.GetLexeme();
	IdentifierNode * in = new IdentifierNode(label);
	return in;
}

IntegerNode * ParserClass::Integer() {
	TokenClass token = Match(INTEGER_TOKEN);
	std::string label = token.GetLexeme();
	const char* cString = label.c_str();
	int tokenInt = atoi(cString);
	IntegerNode * in =  new IntegerNode(tokenInt);
	return in;
}

DeclarationStatementNode * ParserClass::DeclarationStatement() {
	Match(INT_TOKEN);
	IdentifierNode * in = Identifier();
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode* dn = new DeclarationStatementNode(in);
	return dn;
}

AssignmentStatementNode * ParserClass::AssignmentStatement() {
	IdentifierNode * in = Identifier();
	Match(ASSIGNMENT_TOKEN);
	ExpressionNode * exp = Expression();
	Match(SEMICOLON_TOKEN);
	
	// Takes identifier node then a expression node
	AssignmentStatementNode* asn = new AssignmentStatementNode(in, exp);
	return asn;
}

CoutStatementNode * ParserClass::CoutStatement() {
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	Expression();
	Match(SEMICOLON_TOKEN);
}

TokenClass ParserClass::Match(TokenType expectedType) {
	TokenClass currentToken = mScanner->GetNextToken();
	if (currentToken.GetTokenType() != expectedType) {
		std::cerr << "Error in ParserClass::Match. " << std::endl;
		std::cerr << "Expected token type " <<
			TokenClass::GetTokenTypeName(expectedType) <<
			", but got type " << currentToken.GetTokenTypeName()
			<< std::endl;
		exit(1);
	}
	MSG("\tSuccessfully matched Token: " <<
		currentToken.GetTokenTypeName() << ". Lexeme: \"" <<
		currentToken.GetLexeme() << "\"");
	return currentToken;
}
