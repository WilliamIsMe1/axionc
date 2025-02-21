#ifndef LEXEME_CPP
#define LEXEME_CPP
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
    case COMMENT: return "COMMENT";
    case ARITHMETIC_OPERATOR: return "ARITHMETIC_OPERATOR";
    case COMPARISON_OPERATOR: return "COMPARISON_OPERATOR";
    case LOGIC_OPERATOR: return "LOGIC_OPERATOR";
    case BITWISE_OPERATOR: return "BITWISE_OPERATOR";
    case ASSIGNMENT_OPERATOR: return "ASSIGNMENT_OPERATOR";
    case MACRO_LINE: return "MACRO_LINE";
    case NEWLINE: return "NEWLINE";
    case WHITESPACE_MARKER: return "WHITESPACE_MARKER";
    case PUNCTUATION: return "PUNCTUATION";
    case LEFT_BRACE: return "LEFT_BRACE";
    case LEFT_PARENTHESIS: return "LEFT_PARENTHESIS";
    case LEFT_BRACKET: return "LEFT_BRACKET";
    case RIGHT_BRACKET: return "RIGHT_BRACKET";
    case RIGHT_PARENTHESIS: return "RIGHT_PARENTHESIS";
    case RIGHT_BRACE: return "RIGHT_BRACE";
    case IDENTIFIER: return "IDENTIFIER";
    case ANNOTATION: return "ANNOTATION";
    case KEYWORD: return "KEYWORD";
    case ERROR: return "ERROR";
    default: return "UNKNOWN";
    }
}


#endif