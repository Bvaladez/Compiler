#pragma once

#include "Token.h"

// LAST_* used for knowing the num of items in the enum
enum MachineState {
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
	ADDITION_STATE, SUBTRACTION_STATE, MULTIPLICATION_STATE, DIVISION_STATE,
	INSERTION_STATE, ASSIGNMENT_STATE, LESS_STATE, LESSEQUAL_STATE,
	GREATER_STATE, GREATEREQUAL_STATE, EQUAL_STATE, NOTEQUAL_STATE, 
	SEMICOLON_STATE, LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE,
	ENDFILE_STATE, LINECOMMENT_STATE, BLOCKCOMMENTOPEN_STATE, 
	BLOCKCOMMENTCLOSE_STATE,
	BAD_STATE,

	LAST_STATE
};

enum CharacterType {
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, MINUS_CHAR,
	TIMES_CHAR, DIVIDE_CHAR, INSERTION_CHAR, ASSIGNMENT_CHAR,
	LESS_CHAR, LESSEQUAL_CHAR, GREATER_CHAR, GREATEREQUAL_CHAR,
	EQUAL_CHAR, NOTEQUAL_CHAR, SEMICOLON_CHAR, LPAREN_CHAR, RPAREN_CHAR,
	LCURLY_CHAR, RCURLY_CHAR, ENDFILE_CHAR, NEWLINE_CHAR,
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
