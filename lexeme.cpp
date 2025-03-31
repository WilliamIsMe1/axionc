#include "lexeme.hpp"
#include <deque>

using namespace std;

token createToken(int line, int column, TokenType tokenType, string contents, deque<token>& tokenStack)
{
    token t = {tokenType, line, column, contents};
    tokenStack.push_back(t);
    return t;
}

string getTokenName(TokenType token) {
    switch (token) {
    case NUMBER_LITERAL: return "NUMBER_LITERAL";
    case HEX_LITERAL: return "HEX_LITERAL";
    case STRING_LITERAL: return "STRING_LITERAL";
    case BOOLEAN_LITERAL: return "BOOLEAN_LITERAL";
    case IDENTIFIER: return "IDENTIFIER";
    case COMMENT: return "COMMENT";

        // Additive Operators
    case PLUS: return "PLUS";
    case MINUS: return "MINUS";
    case PLUS_PLUS: return "PLUS_PLUS";
    case MINUS_MINUS: return "MINUS_MINUS";

        // Multiplicative Operators
    case STAR: return "STAR";
    case SLASH: return "SLASH";
    case STAR_STAR: return "STAR_STAR";
    case COLON: return "COLON";

        // Comparison Operators
    case L_ANGLE: return "L_ANGLE";
    case R_ANGLE: return "R_ANGLE";
    case L_ANGLE_EQUALS: return "L_ANGLE_EQUALS";
    case R_ANGLE_EQUALS: return "R_ANGLE_EQUALS";
    case BANG_EQUALS: return "BANG_EQUALS";
    case EQUALS_EQUALS: return "EQUALS_EQUALS";
    case EQUALS_EQUALS_EQUALS: return "EQUALS_EQUALS_EQUALS";
    case BANG_EQUALS_EQUALS: return "BANG_EQUALS_EQUALS";

        // Logic Operators
    case AMPERSAND_AMPERSAND: return "AMPERSAND_AMPERSAND";
    case PIPE_PIPE: return "PIPE_PIPE";
    case BANG: return "BANG";
    case CARET_CARET: return "CARET_CARET";

        // Bitwise Operators
    case AMPERSAND: return "AMPERSAND";
    case PIPE: return "PIPE";
    case CARET: return "CARET";
    case L_ANGLE_L_ANGLE: return "L_ANGLE_L_ANGLE";
    case R_ANGLE_R_ANGLE: return "R_ANGLE_R_ANGLE";
    case TILDE: return "TILDE";

        // Assignment Operators
    case EQUALS: return "EQUALS";
    case PLUS_EQUALS: return "PLUS_EQUALS";
    case MINUS_EQUALS: return "MINUS_EQUALS";
    case STAR_EQUALS: return "STAR_EQUALS";
    case SLASH_EQUALS: return "SLASH_EQUALS";
    case MOD_EQUALS: return "MOD_EQUALS";
    case STAR_STAR_EQUALS: return "STAR_STAR_EQUALS";
    case AMPERSAND_EQUALS: return "AMPERSAND_EQUALS";
    case PIPE_EQUALS: return "PIPE_EQUALS";
    case CARET_EQUALS: return "CARET_EQUALS";


        // Punctuation
    case DOT: return "DOT";
    case COMMA: return "COMMA";
    case SEMICOLON: return "SEMICOLON";
    case COLON_COLON: return "COLON_COLON";

        // Stuff
    case L_BRACE: return "L_BRACE";
    case L_PAREN: return "L_PAREN";
    case L_BRACKET: return "L_BRACKET";
    case R_BRACKET: return "R_BRACKET";
    case R_PAREN: return "R_PAREN";
    case R_BRACE: return "R_BRACE";

    case AT: return "AT";

        // Special cases
    case MACRO_LINE: return "MACRO_LINE";
    case NEWLINE: return "NEWLINE";
    case WHITESPACE_MARKER: return "WHITESPACE_MARKER";

        // Keywords
    case KEYWORD_ABSTRACT: return "KEYWORD_ABSTRACT";
    case KEYWORD_ASSERT: return "KEYWORD_ASSERT";
    case KEYWORD_BREAK: return "KEYWORD_BREAK";
    case KEYWORD_CASE: return "KEYWORD_CASE";
    case KEYWORD_CATCH: return "KEYWORD_CATCH";
    case KEYWORD_CLASS: return "KEYWORD_CLASS";
    case KEYWORD_CLOSURE: return "KEYWORD_CLOSURE";
    case KEYWORD_CONTINUE: return "KEYWORD_CONTINUE";
    case KEYWORD_DEFAULT: return "KEYWORD_DEFAULT";
    case KEYWORD_DO: return "KEYWORD_DO";
    case KEYWORD_ELSE: return "KEYWORD_ELSE";
    case KEYWORD_ENUM: return "KEYWORD_ENUM";
    case KEYWORD_EXTENDS: return "KEYWORD_EXTENDS";
    case KEYWORD_FINAL: return "KEYWORD_FINAL";
    case KEYWORD_FINALLY: return "KEYWORD_FINALLY";
    case KEYWORD_FOR: return "KEYWORD_FOR";
    case KEYWORD_IF: return "KEYWORD_IF";
    case KEYWORD_IMPLEMENTS: return "KEYWORD_IMPLEMENTS";
    case KEYWORD_IMPORT: return "KEYWORD_IMPORT";
    case KEYWORD_ISOFTYPE: return "KEYWORD_ISOFTYPE";
    case KEYWORD_INTERFACE: return "KEYWORD_INTERFACE";
    case KEYWORD_MODULE: return "KEYWORD_MODULE";
    case KEYWORD_NATIVE: return "KEYWORD_NATIVE";
    case KEYWORD_NEW: return "KEYWORD_NEW";
    case KEYWORD_NONSEALED: return "KEYWORD_NONSEALED";
    case KEYWORD_PERMITS: return "KEYWORD_PERMITS";
    case KEYWORD_PRIVATE: return "KEYWORD_PRIVATE";
    case KEYWORD_PROTECTED: return "KEYWORD_PROTECTED";
    case KEYWORD_PUBLIC: return "KEYWORD_PUBLIC";
    case KEYWORD_RETURN: return "KEYWORD_RETURN";
    case KEYWORD_SEALED: return "KEYWORD_SEALED";
    case KEYWORD_STATIC: return "KEYWORD_STATIC";
    case KEYWORD_SUPER: return "KEYWORD_SUPER";
    case KEYWORD_SWITCH: return "KEYWORD_SWITCH";
    case KEYWORD_THIS: return "KEYWORD_THIS";
    case KEYWORD_THROW: return "KEYWORD_THROW";
    case KEYWORD_THROWS: return "KEYWORD_THROWS";
    case KEYWORD_TRY: return "KEYWORD_TRY";
    case KEYWORD_VOID: return "KEYWORD_VOID";
    case KEYWORD_WHILE: return "KEYWORD_WHILE";
    case KEYWORD_OPERATOR: return "KEYWORD_OPERATOR";
    case KEYWORD_REQUIRES: return "KEYWORD_REQUIRES";
    case KEYWORD_EXPORTS: return "KEYWORD_EXPORTS";
    case KEYWORD_IN: return "KEYWORD_IN";
    case KEYWORD_GLOBAL: return "KEYWORD_GLOBAL";

    case PRIMITIVE_TYPE: return "PRIMITIVE_TYPE";
    case ERROR: return "ERROR";
    case EOF_: return "EOF";

    default: return "Invalid token type";
    }
}
