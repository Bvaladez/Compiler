#include "Parser.h"
#include "Debug.h"


ParserClass::ParserClass(ScannerClass* Scanner, SymbolTableClass* SymbolTable) {
	mScanner = Scanner;
	mSymbolTable = SymbolTable;
}

void ParserClass::Start() {
	Program();
	Match(ENDFILE_TOKEN);
}

void ParserClass::Program() {
	Match(VOID_TOKEN);
	Match(MAIN_TOKEN);
	Match(LPAREN_TOKEN);
	Match(RPAREN_TOKEN);
	Block();
}

void ParserClass::Block() {
	Match(LCURLY_TOKEN);
	StatementGroup();
	Match(RCURLY_TOKEN);
}

void ParserClass::StatementGroup() {
	bool check;
	do {
		check = Statement();
	}
	while (check);
}

bool ParserClass::Statement() {
	TokenClass Token = mScanner->PeekNextToken();
	TokenType tt = Token.GetTokenType();
	if (tt == INT_TOKEN) {
		DeclarationStatement();
		return true;
	}
	else if (tt == IDENTIFIER_TOKEN) {
		AssignmentStatement();
		return true;
	}
	else if (tt == COUT_TOKEN) {
		CoutStatement();
		return true;
	}
	else {
		return false;
	}

}

void ParserClass::Expression() {
	Relational();
}

void ParserClass::Relational() {
	PlusMinus();

	//handle optional tail (LL1 parser)
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == LESS_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if(tt == LESSEQUAL_TOKEN){
		Match(tt);
		PlusMinus();
	}
	else if (tt == GREATER_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if (tt == GREATEREQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if (tt == EQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else if (tt == NOTEQUAL_TOKEN) {
		Match(tt);
		PlusMinus();
	}
	else {
		return;
	}
}

void ParserClass::PlusMinus() {
	TimesDivide();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == PLUS_TOKEN)
		{
			Match(tt);
			TimesDivide();
		}
		else if (tt == MINUS_TOKEN)
		{
			Match(tt);
			TimesDivide();
		}
		else
		{
			return;
		}
	}
}

void ParserClass::TimesDivide() {
	Factor();
	while (true) {
		TokenType tt = mScanner->PeekNextToken().GetTokenType();
		if (tt == TIMES_TOKEN) {
			Match(tt);
			Factor();
		}
		else if (tt == DIVIDE_TOKEN) {
			Match(tt);
			Factor();
		}
		else {
			return;
		}
	}
}

void ParserClass::Factor() {
	TokenType tt = mScanner->PeekNextToken().GetTokenType();
	if (tt == IDENTIFIER_TOKEN) {
		Identifier();
	}
	else if (tt == INTEGER_TOKEN) {
		Integer();
	}
	else if (tt == LPAREN_TOKEN) {
		Expression();
		Match(RPAREN_TOKEN);
	}
	else {
		std::cerr << "Unexpected Token --> " << tt << std::endl;
		std::exit(1);
	}
	
}

void ParserClass::Identifier() {
	Match(IDENTIFIER_TOKEN);
}

void ParserClass::Integer() {
	Match(INTEGER_TOKEN);
}

void ParserClass::DeclarationStatement() {
	Match(INT_TOKEN);
	Identifier();
	Match(SEMICOLON_TOKEN);
}

void ParserClass::AssignmentStatement() {
	Identifier();
	Match(ASSIGNMENT_TOKEN);
	Expression();
	Match(SEMICOLON_TOKEN);
}
void ParserClass::CoutStatement() {
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