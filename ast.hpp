#pragma once

#include <string>
#include <vector>
#include <memory>
#include <any>
#include <iostream>

#include "lexeme.hpp"

using namespace std;

// This is a simple NonTerminal enum that represents an AST node type
enum NonTerminal {
	PROGRAM,
	STATEMENT,
	BLOCK,
	EXPRESSION,
	BINARYOP
};

// This is a simple Grammar atom that can be either a terminal or a non-terminal
// It is used to represent production rules in the shift-reduce 1 lookahead parser
typedef struct  {
	union {
		NonTerminal nonTerminal;
		TokenType terminal;
	} value;
	bool isTerminal;
} GrammarAtom;

// This is a production rule struct that can be used to reduce to a nonterminal.
typedef struct {
	GrammarAtom rightHandSide[10]; // The 
	GrammarAtom lookaheadNot[10]; // All the look aheads that don't match the rule
	NonTerminal leftHandSide; // The nonterminal that the rule reduces to
} ProductionRule;
