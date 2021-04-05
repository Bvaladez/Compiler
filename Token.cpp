#include "Token.h"
#include "debug.h"

#include <iomanip>
#include <iostream>

TokenClass::TokenClass(TokenType type, const std::string& lexeme) {
	mType = type;
	mLexeme = lexeme;
	this->CheckReserved();
}
void TokenClass::CheckReserved() {
	std::string lexeme = GetLexeme();
	if (lexeme == "void") {
		mType = TokenType::VOID_TOKEN;
	}
	else if (lexeme == "main") {
		mType = TokenType::MAIN_TOKEN;
	}
	else if (lexeme == "int") {
		mType = TokenType::INT_TOKEN;
	}
	else if (lexeme == "cout") {
		mType = TokenType::COUT_TOKEN;
	}
	else if (lexeme == "if") {
		mType = TokenType::IF_TOKEN;
	}
	else if (lexeme == "while") {
		mType = TokenType::WHILE_TOKEN;
	}
	return;
}

std::ostream& operator<<(std::ostream& out, const TokenClass& tc) {
	// formats the text toe be justified even if lines have different chars	
	out.setf(std::ios::left);
	out << "Type: " << std::setw(15) << tc.GetTokenTypeName()
		<< "Lexeme: " << std::setw(15) << tc.GetLexeme();
	return out;


	//TokenType tt = tc.GetTokenType();
	//return out << "TokenType: " << tt 
	//			<< " Token Name: " << tc.GetTokenTypeName(tt) 
	//		<< " Lexeme: " << tc.GetLexeme() << std::endl;
}
