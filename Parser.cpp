#include "Parser.h"
#include "Debug.h"


ParserClass::ParserClass(ScannerClass* Scanner, SymbolTableClass* SymbolTable) {
	mScanner = Scanner;
	mSymbolTable = SymbolTable;
}

ParserClass::~ParserClass() {

}

StartNode * ParserClass::Start() {
	MSG("Parser Starting...")
	ProgramNode* pn = Program();
	Match(ENDFILE_TOKEN);
	StartNode* sn = new StartNode(pn);
	return sn;
}

ProgramNode * ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	BlockNode* bn = Block();
	ProgramNode* pn = new ProgramNode(bn);
	return pn;
}

BlockNode * ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroupNode* sgn = StatementGroup();
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
		StatementNode * ds = DeclarationStatement();
		return ds;
	}
	else if (tt == IDENTIFIER_TOKEN) {
		StatementNode* as = AssignmentStatement();
		return as;
	}
	else if (tt == COUT_TOKEN) {
	
	 	StatementNode* cs = CoutStatement();
		return cs;
	}
	else if (tt == IF_TOKEN) {
		StatementNode* is = IfStatement();
		return is;
	}
	else if (tt == WHILE_TOKEN) {
		StatementNode* ws = WhileStatement();
		return ws;
	}
	else {
		return NULL;
	}

}

ExpressionNode *  ParserClass::Expression() {
	return OrStatement();
}

ExpressionNode* ParserClass::OrStatement() {
	ExpressionNode* current = AndStatement();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == OR_TOKEN) {
			Match(tt);
			current = new OrNode(current, AndStatement());
		}
		else {
			return current;
		}
	}
}

ExpressionNode* ParserClass::AndStatement() {
	ExpressionNode* current = BitwiseAndStatement();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == AND_TOKEN) {
			Match(tt);
			current = new AndNode(current, Relational());
		}
		else {
			return current;
		}
	}

}

ExpressionNode* ParserClass::BitwiseAndStatement() {
	ExpressionNode* current = Relational();
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == BITWISE_AND_TOKEN) {
		Match(tt);
		current = new BitwiseAndNode(current, Relational());
	}
	else {
		return current;
	}

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
	ExpressionNode * current  = Exponent();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN)
		{
			Match(tt);
			current = new PlusNode(current, Exponent());
		}
		else if (tt == MINUS_TOKEN)
		{
			Match(tt);
			current = new MinusNode(current, Exponent());
		}
		else
		{
			return current;
		}
	}
}

ExpressionNode * ParserClass::Exponent() {
	ExpressionNode * current  = TimesDivide();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == EXP_TOKEN)
		{
			Match(tt);
			current = new ExpNode(current, TimesDivide());
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
	IdentifierNode * in = new IdentifierNode(label, mSymbolTable);
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
	// Give it an itial value
	if (mScanner->PeekNextToken().GetTokenType() == ASSIGNMENT_TOKEN) {
		Match(ASSIGNMENT_TOKEN);
		ExpressionNode* exp = Expression();
		Match(SEMICOLON_TOKEN);
		DeclarationStatementNode* dn = new DeclarationStatementNode(in, exp);
		return dn;
	}
	// Dont give it an initial value
	Match(SEMICOLON_TOKEN);
	DeclarationStatementNode* dn = new DeclarationStatementNode(in, NULL);
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

IfStatementNode* ParserClass::IfStatement() {
	Match(IF_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* exp = Expression();
	Match(RPAREN_TOKEN);
	BlockNode* ibn = Block();
	if (mScanner->PeekNextToken().GetTokenType() == TokenType::ELSE_TOKEN) {
		Match(ELSE_TOKEN);
		BlockNode* ebn = Block();
		IfStatementNode* iesn = new IfStatementNode(exp, ibn, ebn);
		return iesn;
	}
	IfStatementNode* isn = new IfStatementNode(exp, ibn, NULL);
	return isn;
}

WhileStatementNode* ParserClass::WhileStatement() {
	Match(WHILE_TOKEN);
	Match(LPAREN_TOKEN);
	ExpressionNode* exp = Expression();
	Match(RPAREN_TOKEN);
	BlockNode* bn = Block();
	WhileStatementNode* wsn = new WhileStatementNode(exp, bn);
	return wsn;
}

CoutStatementNode * ParserClass::CoutStatement() {
	Match(COUT_TOKEN);
	Match(INSERTION_TOKEN);
	ExpressionNode * exp = Expression();
	Match(SEMICOLON_TOKEN);
	CoutStatementNode* csn = new CoutStatementNode(exp);
	return csn;
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
