#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
using namespace std;

struct GrammarRule {
	string input_rule[100];
	string lookahead;
};


#endif