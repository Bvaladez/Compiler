#pragma once

#include <string>
#include <ostream>

enum TokenType {
	// Reserved Words:
	VOID_TOKEN, MAIN_TOKEN, INT_TOKEN, COUT_TOKEN, IF_TOKEN, WHILE_TOKEN,
	// Relational Operators:
	LESS_TOKEN, LESSEQUAL_TOKEN, GREATER_TOKEN, GREATEREQUAL_TOKEN, EQUAL_TOKEN, NOTEQUAL_TOKEN,
	// Other Operators:
	INSERTION_TOKEN, ASSIGNMENT_TOKEN, PLUS_TOKEN, MINUS_TOKEN, TIMES_TOKEN, DIVIDE_TOKEN, BITWISE_AND_TOKEN, AND_TOKEN, BITWISE_OR_TOKEN, OR_TOKEN,
	// Other Characters:
	SEMICOLON_TOKEN, LPAREN_TOKEN, RPAREN_TOKEN, LCURLY_TOKEN,
	RCURLY_TOKEN,
	// Other Token Types:
	IDENTIFIER_TOKEN, INTEGER_TOKEN,
	BAD_TOKEN, ENDFILE_TOKEN
};

// IMPORTANT: The list above and the list below MUST be kept in sync.
const std::string gTokenTypeNames[] = {
	"VOID", "MAIN", "INT", "COUT", "IF", "WHILE",
	"LESS", "LESSEQUAL", "GREATER", "GREATEREQUAL", "EQUAL", "NOTEQUAL",
	"INSERTION", "ASSIGNMENT", "PLUS", "MINUS", "TIMES", "DIVIDE", "BITWISEAND", "AND", "BITWISEOR" ,"OR"
	"SEMICOLON", "LPAREN", "RPAREN", "LCURLY", "RCURLY",
	"IDENTIFIER", "INTEGER",
	"BAD", "ENDFILE"
};

class TokenClass{

public:
	//TokenClass();
	//~TokenClass();
	TokenClass(TokenType type, const std::string& lexeme);
	TokenType GetTokenType() const { return mType; }
	const std::string& GetTokenTypeName() const{
		return gTokenTypeNames[mType];
	}
	std::string GetLexeme() const { return mLexeme; }
	static const std::string& GetTokenTypeName(TokenType type){
		return gTokenTypeNames[type];
	}
	// check if the lexeme is a reserved word, if so changes mType to correct TokenType
	void CheckReserved();

private:
	TokenType mType;
	std::string mLexeme;
};

std::ostream& operator<<(std::ostream& out, const TokenClass& tc);


