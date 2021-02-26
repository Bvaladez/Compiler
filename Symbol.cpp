#include <iostream>
#include "Symbol.h"	



bool SymbolTableClass::Exists(const std::string& s) {
	for (int i = 0; i < mSymbolTable.size(); i++) {
		if (this->mSymbolTable[i].mLabel == s) {
			return true;
		}
		else {
			return false;
		}
	}
}

void SymbolTableClass::AddEntry(const std::string& s) {
	if (!Exists(s)) {
		Variable v;
		v.mLabel = s;
		v.mValue = -1;
		mSymbolTable.push_back(v);
	}
	else {
		exit(0);
	}
}

int SymbolTableClass::GetValue(const std::string& s) {
	if (Exists(s)) {
		return this->mSymbolTable[GetIndex(s)].mValue;
	}
	else {
		std::cout << "Variable " << s << " does not exist in the symbol table, could not get value. " << std::endl;
		exit(0);
	}
}

void SymbolTableClass::SetValue(const std::string& s, int v) {
	if (Exists(s)) {
		this->mSymbolTable[GetIndex(s)].mValue = v;
	}
	else {
		std::cout << "Variable " << s << " does not exist in the symbol table, could not update value. " << std::endl;
		exit(0);
	}
}

int SymbolTableClass::GetIndex(const std::string& s) {
	for (int i = 0; i < mSymbolTable.size(); i++) {
		if (this->mSymbolTable[i].mLabel == s) {
			return i;
		}
	}
	// The label was not in the symbol table.
	return -1;
}

int SymbolTableClass::GetCount() {
	return this->mSymbolTable.size();
}

