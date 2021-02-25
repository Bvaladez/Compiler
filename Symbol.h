#pragma once
#include <string>

class SymboolTableClass {

public:
	bool Exists(const std::string& s);
	void AddEntry(const std::string& s);
	int GetValue(const std::string& s);
	void SetValue(const std::string& s, int v);
	int GetIndex(const std::string& s);
	int GetCount();

private:


};
