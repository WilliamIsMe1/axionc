#include <iostream>
#include <fstream>
#include "lexer.hpp"

using namespace std;

void printTokens() {
	cout << "[" << endl;
	while (!tokenStack.empty()) {
		token Token = tokenStack.front();
		tokenStack.pop_front();
		cout << "{type:" << getTokenName(Token.type)
			<< ",lineNum:" << Token.lineNum
			<< ",columnNum:" << Token.columnNum
			<< ",contents:" << Token.contents
			<< "}";
		if (!tokenStack.empty()) {
			cout << ",";
		}
		cout << endl;
	}
	cout << "]";
}

int main(int argc, char* argv[]) 
{
	ifstream fin("./test.ax");
	if (!fin) {
		cerr << "Failed to open file." << endl;
		return 1;
	}
	scanFile(fin);
	printTokens();
	return 0;
}

