#pragma once
#include <string>
#include <deque>
using namespace std;

// A token type enum for a lexeme
enum TokenType {
	// Literals
	NUMBER_LITERAL, // (-)?\d+(\.\d+)?([Ee][+-]\d+)?([fFlLDd]?) Matches 1 1.0 1e10 1.0e10 -10
	HEX_LITERAL, // 0[xX][0-9a-fA-F]+(\.[0-9a-fA-F]+)?([pP][+-]?\d+)? Matches hex literals
	STRING_LITERAL, // "([^"\\]*(\\.[^"\\]*)*)" Matches any string literal without \ or ", but allows escape sequences
	BOOLEAN_LITERAL, // true|false

	// Identifier
	IDENTIFIER, // (?!\d)(?!_+$)(?!.*__)[a-zA-Z0-9_]+ Cannot only be underscores, cannot start with a number

	// Comment
	COMMENT, /* \/\/.*|\/\*[\s\S]*?\*\/ Matches any single line comment and multiline comment */

	// Additive Operators
	PLUS,
	MINUS,
	PLUS_PLUS,
	MINUS_MINUS,

	// Multiplicative Operators
	STAR,
	SLASH,
	STAR_STAR,
	COLON, // The ratio operator. It doesn't bind tightly, as it is for ratios, not division.

	// Comparison operators
	L_ANGLE,
	R_ANGLE,
	BANG_EQUALS,
	EQUALS_EQUALS,
	EQUALS_EQUALS_EQUALS,
	BANG_EQUALS_EQUALS,
	L_ANGLE_EQUALS,
	R_ANGLE_EQUALS,

	// Logic Operators
	AMPERSAND_AMPERSAND,
	PIPE_PIPE,
	BANG,
	CARET_CARET,

	// Bitwise Operators
	AMPERSAND,
	PIPE,
	CARET,
	TILDE, 
	L_ANGLE_L_ANGLE,
	R_ANGLE_R_ANGLE,

	// Assignment Operators
	EQUALS,
	PLUS_EQUALS,
	MINUS_EQUALS,
	STAR_EQUALS,
	SLASH_EQUALS,
	MOD_EQUALS,
	STAR_STAR_EQUALS,
	AMPERSAND_EQUALS,
	PIPE_EQUALS,
	CARET_EQUALS,

	// Punctuation
	DOT,
	COMMA,
	SEMICOLON,
	COLON_COLON,
	
	// Stuff
	L_BRACE, // {
	L_PAREN, // (
	L_BRACKET, // [
	R_BRACKET, // ]
	R_PAREN, // )
	R_BRACE, // }

	AT, // Matches a @ symbol

	MACRO_LINE, // ^#.* Matches any line with a # at the start
	NEWLINE, // Appended after a line is processed, unless working on a multiline comment
	WHITESPACE_MARKER, // Marks any whitespace that isn't a line break
	KEYWORD_ABSTRACT,
	KEYWORD_ASSERT,
	KEYWORD_BREAK,
	KEYWORD_CASE,
	KEYWORD_CATCH,
	KEYWORD_CLASS,
	KEYWORD_CLOSURE,
	KEYWORD_CONTINUE,
	KEYWORD_DEFAULT,
	KEYWORD_DO,
	KEYWORD_ELSE,
	KEYWORD_ENUM,
	KEYWORD_EXTENDS,
	KEYWORD_FINAL,
	KEYWORD_FINALLY,
	KEYWORD_FOR,
	KEYWORD_IF,
	KEYWORD_IMPLEMENTS,
	KEYWORD_IMPORT,
	KEYWORD_ISOFTYPE,
	KEYWORD_INTERFACE,
	KEYWORD_MODULE,
	KEYWORD_NATIVE,
	KEYWORD_NEW,
	KEYWORD_NONSEALED,
	KEYWORD_PERMITS,
	KEYWORD_PRIVATE,
	KEYWORD_PROTECTED,
	KEYWORD_PUBLIC,
	KEYWORD_RETURN,
	KEYWORD_SEALED,
	KEYWORD_STATIC,
	KEYWORD_SUPER,
	KEYWORD_SWITCH,
	KEYWORD_THIS,
	KEYWORD_THROW,
	KEYWORD_THROWS,
	KEYWORD_TRY,
	KEYWORD_VOID,
	KEYWORD_WHILE,
	KEYWORD_OPERATOR,
	KEYWORD_REQUIRES,
	KEYWORD_EXPORTS,
	KEYWORD_IN,
	KEYWORD_GLOBAL,
	PRIMITIVE_TYPE,
	ERROR, // For errors
	EOF_
};

typedef struct {
	TokenType type;
	int lineNum;
	int columnNum;
	string contents;
} token;


token createToken(int line, int column, TokenType tokenType, string contents, deque<token>& tokenStack);

string getTokenName(TokenType token);