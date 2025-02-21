#ifndef AXION_LEXEME_HPP
#define AXION_LEXEME_HPP

#include <string>
#include <deque>
using namespace std;

// A token type enum for a lexeme
enum TokenType {
	NUMBER_LITERAL, // (-)?\d+(\.\d+)?([Ee][+-]\d+)?([fFlLDd]?) Matches 1 1.0 1e10 1.0e10 -10
	HEX_LITERAL, // 0[xX][0-9a-fA-F]+(\.[0-9a-fA-F]+)?([pP][+-]?\d+)? Matches hex literals
	STRING_LITERAL, // "([^"\\]*(\\.[^"\\]*)*)" Matches any string literal without \ or ", but allows escape sequences
	COMMENT, // \/\/.*|\/\*[\s\S]*?\*\/ Matches any single line comment and multiline comment
	ARITHMETIC_OPERATOR, // Consumes +, -, *, /, ++, --, **, :
	COMPARISON_OPERATOR, // Consumes >, <, >=, <=, !=, ==, ===, !== 
	LOGIC_OPERATOR, // Consumes &&, ||, !, ^^
	BITWISE_OPERATOR, // Consumes &, |, ^, <<, >>
	ASSIGNMENT_OPERATOR, // Consumes =, +=, -=, *=, /=, **=, &=, |=, ^=
	MACRO_LINE, // ^#.* Matches any line with a # at the start
	NEWLINE, // Appended after a line is processed, unless working on a multiline comment
	WHITESPACE_MARKER, // Marks any whitespace that isn't a line break
	PUNCTUATION, // Matches . and , and ;
	LEFT_BRACE, // {
	LEFT_PARENTHESIS, // (
	LEFT_BRACKET, // [
	RIGHT_BRACKET, // ]
	RIGHT_PARENTHESIS, // )
	RIGHT_BRACE, // }
	IDENTIFIER, // (?!\d)(?!_+$)(?!.*__)[a-zA-Z0-9_]+ Cannot only be underscores, cannot start with a number, cannot
	ANNOTATION, // Matches a @ symbol
	KEYWORD, // For reserved keywords
	ERROR // For errors

};

typedef struct {
	TokenType type;
	int lineNum;
	int columnNum;
	string contents;
} token;


token createToken(int line, int column, TokenType tokenType, string contents, deque<token>& tokenStack);

string getTokenName(TokenType token);
#endif