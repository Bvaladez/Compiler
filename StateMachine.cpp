#include "StateMachine.h"
#include "debug.h"

StateMachineClass::StateMachineClass() {

	mCurrentState = START_STATE;

	// fill all space to be Illegal states then change all those that are legal
	for (int i = 0; i < LAST_STATE; i++) {
		for (int j = 0; j < LAST_CHAR; j++) {
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}
	
	// WHITESPACE //
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][NEWLINE_CHAR] = START_STATE;
	
	// IDENTIFIER STATES //
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR] = IDENTIFIER_STATE;

	// INTEGER STATES //
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;

	// ADDITION //
	mLegalMoves[START_STATE][PLUS_CHAR] = ADDITION_STATE;
	
	// SUBTRACTION //
	mLegalMoves[START_STATE][MINUS_CHAR] = SUBTRACTION_STATE;
	
	// MULTIPLICATION //
	mLegalMoves[START_STATE][TIMES_CHAR] = MULTIPLICATION_STATE;

	// DIVISION //
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVISION_STATE;

	// BLOCK COMMENTS //
	mLegalMoves[DIVISION_STATE][TIMES_CHAR] = BLOCKCOMMENTOPEN_STATE;

	for (int CHAR = 0; CHAR < LAST_CHAR; CHAR++) {
		if (CHAR != TIMES_CHAR) {
			// during a block comment we dont check anything other state until we see *
			mLegalMoves[BLOCKCOMMENTOPEN_STATE][CHAR] = BLOCKCOMMENTOPEN_STATE;
		}
		else {
			mLegalMoves[BLOCKCOMMENTOPEN_STATE][CHAR] = BLOCKCOMMENTCLOSE_STATE;
		}
	}

	for (int CHAR = 0; CHAR < LAST_CHAR; CHAR++) {
		if (CHAR != DIVIDE_CHAR && CHAR != TIMES_CHAR) {
			mLegalMoves[BLOCKCOMMENTCLOSE_STATE][CHAR] = BLOCKCOMMENTOPEN_STATE;
		}
	}
		// Special cases for block comments
		mLegalMoves[BLOCKCOMMENTCLOSE_STATE][TIMES_CHAR] = BLOCKCOMMENTCLOSE_STATE;
		mLegalMoves[BLOCKCOMMENTCLOSE_STATE][DIVIDE_CHAR] = START_STATE;

	// LINE COMMENTS //
	mLegalMoves[DIVISION_STATE][DIVIDE_CHAR] = LINECOMMENT_STATE;

	// for line comments we are okay as long as we dont see a newline or EOF
	for (int CHAR = 0; CHAR < LAST_CHAR; CHAR++) {
		if (CHAR != ENDFILE_CHAR && CHAR != NEWLINE_CHAR) {
			mLegalMoves[LINECOMMENT_STATE][CHAR] = LINECOMMENT_STATE;
		}
	}
		// special cases to end a line comment
		mLegalMoves[LINECOMMENT_STATE][ENDFILE_CHAR] = ENDFILE_STATE;
		mLegalMoves[LINECOMMENT_STATE][NEWLINE_CHAR] = START_STATE;


	// & //
		mLegalMoves[START_STATE][BITWISE_AND_CHAR] = BITWISE_AND_STATE;

	// && //
		mLegalMoves[BITWISE_AND_STATE][BITWISE_AND_CHAR] = AND_STATE;

	// | //
		mLegalMoves[START_STATE][BITWISE_OR_CHAR] = BITWISE_OR_STATE;
	// || //
		mLegalMoves[BITWISE_OR_STATE][BITWISE_OR_CHAR] = OR_STATE;

	// SEMICOLON //
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;

	// EOF //
	mLegalMoves[START_STATE][ENDFILE_CHAR] = ENDFILE_STATE;

	// = //
	mLegalMoves[START_STATE][ASSIGNMENT_CHAR] = ASSIGNMENT_STATE;

	// == //
	mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR] = EQUAL_STATE;

	// ! //
	mLegalMoves[START_STATE][EXCLAMATION_CHAR] = NOT_STATE;

	// != //
	mLegalMoves[NOT_STATE][ASSIGNMENT_CHAR] = NOTEQUAL_STATE;

	// > //
	mLegalMoves[START_STATE][GREATER_CHAR] = GREATER_STATE;

	// >= //
	mLegalMoves[GREATER_STATE][ASSIGNMENT_CHAR] = GREATEREQUAL_STATE;

	// < //
	mLegalMoves[START_STATE][LESS_CHAR] = LESS_STATE;

	// <= //
	mLegalMoves[LESS_STATE][ASSIGNMENT_CHAR] = LESSEQUAL_STATE;

	// << //
	mLegalMoves[LESS_STATE][LESS_CHAR] = INSERTION_STATE;
	
	// ( //
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;

	// ) //
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;

	// { //
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE; 

	// } //
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE; 

	// SET STATES CORRESPONDING TOKENS
	for (int STATE = 0; STATE < LAST_STATE; STATE++) {
		mCorrespondingTokenTypes[STATE] = BAD_TOKEN;
	}
	mCorrespondingTokenTypes[IDENTIFIER_STATE] =	IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[INTEGER_STATE] =		INTEGER_TOKEN;
	mCorrespondingTokenTypes[ADDITION_STATE] =		PLUS_TOKEN;
	mCorrespondingTokenTypes[SUBTRACTION_STATE] =	MINUS_TOKEN;
	mCorrespondingTokenTypes[MULTIPLICATION_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVISION_STATE] =		DIVIDE_TOKEN;
	mCorrespondingTokenTypes[ENDFILE_STATE] =		ENDFILE_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] =		SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[GREATER_STATE] =		GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] =	GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[LESS_STATE] =			LESS_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] =		LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] =		INSERTION_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] =		LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] =		RPAREN_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] =		LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] =		RCURLY_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] =	ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] =			EQUAL_TOKEN;
	mCorrespondingTokenTypes[NOTEQUAL_STATE] =		NOTEQUAL_TOKEN;
	mCorrespondingTokenTypes[BITWISE_AND_STATE] =	BITWISE_AND_TOKEN;
	mCorrespondingTokenTypes[BITWISE_OR_STATE] =	BITWISE_OR_TOKEN;
	mCorrespondingTokenTypes[AND_STATE] =			AND_TOKEN;
	mCorrespondingTokenTypes[OR_STATE] =			OR_TOKEN;


}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType &correspondingTokenType) {
	
	CharacterType charType = BAD_CHAR;

	if (isdigit(currentCharacter))
		charType = DIGIT_CHAR;
	if (isalpha(currentCharacter))
		charType = LETTER_CHAR;
	if (isspace(currentCharacter))
		charType = WHITESPACE_CHAR;
	if (currentCharacter == '+')
		charType = PLUS_CHAR;
	if (currentCharacter == '-')
		charType = MINUS_CHAR;
	if (currentCharacter == '*')
		charType = TIMES_CHAR;
	if (currentCharacter == '/')
		charType = DIVIDE_CHAR;
	if (currentCharacter == ';')
		charType = SEMICOLON_CHAR;
	if (currentCharacter == '>')
		charType = GREATER_CHAR;
	if (currentCharacter == '<')
		charType = LESS_CHAR;
	if (currentCharacter == '=')
		charType = ASSIGNMENT_CHAR;
	if (currentCharacter == '!')
		charType = EXCLAMATION_CHAR;
	if (currentCharacter == '(')
		charType = LPAREN_CHAR;
	if (currentCharacter == ')')
		charType = RPAREN_CHAR;
	if (currentCharacter == '{')
		charType = LCURLY_CHAR;
	if (currentCharacter == '}')
		charType = RCURLY_CHAR;
	if (currentCharacter == '|')
		charType = BITWISE_OR_CHAR;
	if (currentCharacter == '||')
		charType = OR_CHAR;
	if (currentCharacter == '&')
		charType = BITWISE_AND_CHAR;
	if (currentCharacter == '&&')
		charType = AND_CHAR;
	//with out newline char we get regular scanning but loose line comments
	if (currentCharacter == '\n')
		charType = NEWLINE_CHAR;
	// eof char
	if (currentCharacter == EOF)
		charType = ENDFILE_CHAR;
// first we set the referenced corresponding token type to know the last token
	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	// then we update the state with the new state
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}

