#include <string>
#include <iostream>
#include <sstream>
#include "Scanner.h"
#include "StateMachine.h"
#include "Token.h"


ScannerClass::ScannerClass(std::string inputFileName){
	mFin.open(inputFileName.c_str(), std::ios::binary);

	if (!mFin.is_open()) {
		std::cout << "Error opening file" << std::endl;
		// Need to quit if the file does not open 
	}
}

ScannerClass::~ScannerClass() {
	mFin.close();
}


TokenClass ScannerClass::GetNextToken() {
	std::stringstream ss;
	char c;
	TokenType tokenType;
	StateMachineClass stateMachine;
	MachineState currentState;

	do{
		c = mFin.get();
		ss << c;
		currentState = stateMachine.UpdateState(c, tokenType);
		if (tokenType == TokenType::BAD_TOKEN) {
			std::cout << gTokenTypeNames[tokenType] << " <-- is not a legal token in current state." <<  std::endl;
			// quit
		}
	} while (currentState != MachineState::CANTMOVE_STATE);

	std::string lexeme = ss.str();
	// the last char grabbed isnt actually used in this toke
	// we must kick it off the lexeme and take unget it from the read stream
	lexeme = lexeme.substr(0, lexeme.size() - 1);
	mFin.unget();
	
	TokenClass tokenClass(tokenType, lexeme);
	tokenClass.CheckReserved();
	return tokenClass;
}
