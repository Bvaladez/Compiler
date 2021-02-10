#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Scanner.h"
#include "StateMachine.h"
#include "Token.h"
#include "debug.h"


ScannerClass::ScannerClass(std::string inputFileName){
	MSG("Scanner Starting...");
	mLineNumber = 1;
	mFin.open(inputFileName.c_str(), std::ios::binary);

	if (!mFin.is_open()) {
		std::cout << "Error opening file" << std::endl;
		std::exit(0);
	}
}

ScannerClass::~ScannerClass() {
	MSG("Destructing Scanner...")
	mFin.close();
}

TokenClass ScannerClass::GetNextToken() {
	std::string s;
	char c;
	TokenType tokenType;
	StateMachineClass stateMachine;
	MachineState currentState;
	do{
		c = mFin.get();

		if (c == '\n') {
			mLineNumber += 1;
		}

		s += c;
		currentState = stateMachine.UpdateState(c, tokenType);

		if (currentState == MachineState::START_STATE) {
			s = "";
		}

	} while (currentState != MachineState::CANTMOVE_STATE);

	if (tokenType == TokenType::BAD_TOKEN) {
		std::cout << c << " <-- is not a legal token in current state." <<  std::endl;
		std::string s;
		std::stringstream ss;
		ss << c;
		ss >> s;
		// we may not to make this a token class item 
		// this is creating a token object of a back token 
		//
		TokenClass t(tokenType, s);
		return t;
	}

	std::string lexeme = s;
	// the last char grabbed isnt actually used in this toke
	// we must kick it off the lexeme and take unget it from the read stream
	lexeme.pop_back();
	mFin.unget();

	if (c == '/n') {
		mLineNumber -= 1;
	}
	
	TokenClass tokenClass(tokenType, lexeme);
	return tokenClass;
}

int ScannerClass::getLineNumber() {
	return mLineNumber;
}
