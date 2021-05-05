#pragma once

#include "Token.h"

// LAST_* used for knowing the num of items in the enum
enum MachineState {
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
	ADDITION_STATE, PLUSEQUAL_STATE, SUBTRACTION_STATE, MINUSEQUAL_STATE, MULTIPLICATION_STATE, TIMESEQUAL_STATE ,DIVISION_STATE, EXP_STATE,
	INSERTION_STATE, ASSIGNMENT_STATE, BITWISE_AND_STATE, AND_STATE, BITWISE_OR_STATE, OR_STATE,
	LESS_STATE, LESSEQUAL_STATE,
	GREATER_STATE, GREATEREQUAL_STATE, EQUAL_STATE, NOTEQUAL_STATE, 
	SEMICOLON_STATE, LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE,
	ENDFILE_STATE, LINECOMMENT_STATE, BLOCKCOMMENTOPEN_STATE, NOT_STATE,
	BLOCKCOMMENTCLOSE_STATE,
	BAD_STATE,

	LAST_STATE
};

enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, PLUSEQUAL_CHAR, MINUS_CHAR, MINUSEQUAL_CHAR, EXP_CHAR,
	TIMES_CHAR, TIMESEQUAL_CHAR, DIVIDE_CHAR, INSERTION_CHAR, ASSIGNMENT_CHAR, BITWISE_AND_CHAR ,AND_CHAR, BITWISE_OR_CHAR, OR_CHAR,
	LESS_CHAR, LESSEQUAL_CHAR, GREATER_CHAR, GREATEREQUAL_CHAR,
	EQUAL_CHAR, NOTEQUAL_CHAR, SEMICOLON_CHAR, LPAREN_CHAR, RPAREN_CHAR,
	LCURLY_CHAR, RCURLY_CHAR, ENDFILE_CHAR, NEWLINE_CHAR, EXCLAMATION_CHAR,
	BAD_CHAR, 

	LAST_CHAR
};

class StateMachineClass {
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType&
		correspondingTokenType);
	MachineState getCurrentState();

private:
	MachineState mCurrentState;

	// The matrix of legal moves
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR];

	// Whick end-machine-states correspond to which token type
	// (non end states correspond to the BAD_TOKEN token type)
	TokenType mCorrespondingTokenTypes[LAST_STATE];

};
