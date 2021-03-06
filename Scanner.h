#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "Token.h"

class ScannerClass{

public:
	ScannerClass(std::string);
	~ScannerClass();

	TokenClass GetNextToken();
	TokenClass PeekNextToken();
	int getLineNumber();
	
private:
	std::ifstream mFin;
	int mLineNumber;

};

