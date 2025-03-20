#include <deque>
#include <string>
#include "lexeme.hpp"
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

deque<token> tokenStack;
bool hadError = false;

deque<string> regex_search_custom(ifstream& file, const regex& pattern) {
    deque<string> matches;
    string line;

    // Read the file line by line
    while (getline(file, line)) {
        line += "\n"; // Because getline doesn't preserve lines
        // Create an iterator to find all matches in the line
        auto words_begin = sregex_iterator(line.begin(), line.end(), pattern);
        auto words_end = sregex_iterator(); // End iterator

        // Iterate through all matches in the line
        for (auto it = words_begin; it != words_end; ++it) {
            matches.push_back(it->str()); // Add each match to the deque
        }
    }

    return matches;
}


void scanFile(ifstream& inStream)
{
    string numberPattern = "(-)?\\d+(\\.\\d*)?([eE][+-]?\\d+)?([fFlLDd]?)";
    string hexPattern = "0[xX][0-9a-fA-F]+(\\.[0-9a-fA-F]+)?([pP][+-]?\\d+)?";
    string stringPattern = "\"([^\\" "\\]*(\\\\.[^\\" "\\]*)*)\"";
    string commentPattern = "(\\/\\/.*|\\/\\*[\\s\\S]*?\\*\\/)";
    string newlinePattern = "(\\r\\n|\\n|\\r)";
    string operatorPattern = "\\+=|^#.*|\\+|==|\\+\\+|-=|--|!=|\\(|\\)|\\.\\.\\.|\\.|=|\\*\\*=|\\*\\*|\\*=|\\*|\\/\\=|\\/|:=|:|\\{|\\}|\\|\\||&&|&=|&|\\|=|@|\\|\\^=|\\^|!|,";
    string identifierPattern = "(?!\\d)(?!_+$)(?!.*__)[a-zA-Z0-9_]+";
    string whiteSpacePattern = "\\s";
    string catchallPattern = "[^\\w\\s]+";
    string fullPattern = numberPattern + "|" + hexPattern + "|" + stringPattern + "|" + commentPattern + "|" + newlinePattern + "|" + operatorPattern + "|" + identifierPattern + "|" + whiteSpacePattern;

    const regex pattern(fullPattern);
    deque<string> sTokens = regex_search_custom(inStream, pattern);  // This is your custom regex_search function

    int lineNum = 1;  // Keep track of line numbers
    int columnNum = 1; // Keep track of column numbers

    while (!sTokens.empty()) {
        string currentToken = sTokens.front();
        sTokens.pop_front();

        TokenType tokenType = ERROR;  // Default token type
        columnNum += currentToken.length();

        // Handle whitespace and newlines first
        if (regex_match(currentToken, regex("(\\r\\n|\\n|\\r)"))) {
            tokenType = NEWLINE;
            lineNum++;
            columnNum = 1;
        }
        else if (regex_match(currentToken, regex("\\s+"))) {
            tokenType = WHITESPACE_MARKER;
        }
        // Handle specific single-character symbols and punctuation
        else if (currentToken == ".") {
            tokenType = DOT;
        }
        else if (currentToken == ",") {
            tokenType = COMMA;
        }
        else if (currentToken == ";") {
            tokenType = SEMICOLON;
        }
        else if (currentToken == "::") {
            tokenType = COLON_COLON;
        }
        else if (currentToken == "(") {
            tokenType = L_PAREN;
        }
        else if (currentToken == ")") {
            tokenType = R_PAREN;
        }
        else if (currentToken == "{") {
            tokenType = L_BRACE;
        }
        else if (currentToken == "}") {
            tokenType = R_BRACE;
        }
        // Handle operators (without regex_match)
        else if (currentToken == "+") {
            tokenType = PLUS;
        }
        else if (currentToken == "-") {
            tokenType = MINUS;
        }
        else if (currentToken == "++") {
            tokenType = PLUS_PLUS;
        }
        else if (currentToken == "--") {
            tokenType = MINUS_MINUS;
        }
        else if (currentToken == "*") {
            tokenType = STAR;
        }
        else if (currentToken == "/") {
            tokenType = SLASH;
        }
        else if (currentToken == "**") {
            tokenType = STAR_STAR;
        }
        else if (currentToken == ":") {
            tokenType = COLON;
        }
        else if (currentToken == "&&") {
            tokenType = AMPERSAND_AMPERSAND;
        }
        else if (currentToken == "||") {
            tokenType = PIPE_PIPE;
        }
        else if (currentToken == "!") {
            tokenType = BANG;
        }
        else if (currentToken == "^^") {
            tokenType = CARET_CARET;
        }
        else if (currentToken == "&") {
            tokenType = AMPERSAND;
        }
        else if (currentToken == "|") {
            tokenType = PIPE;
        }
        else if (currentToken == "^") {
            tokenType = CARET;
        }
        else if (currentToken == "<<") {
            tokenType = L_ANGLE_L_ANGLE;
        }
        else if (currentToken == ">>") {
            tokenType = R_ANGLE_R_ANGLE;
        }
        else if (currentToken == "=") {
            tokenType = EQUALS;
        }
        else if (currentToken == "+=") {
            tokenType = PLUS_EQUALS;
        }
        else if (currentToken == "-=") {
            tokenType = MINUS_EQUALS;
        }
        else if (currentToken == "*=") {
            tokenType = STAR_EQUALS;
        }
        else if (currentToken == "/=") {
            tokenType = SLASH_EQUALS;
        }
        else if (currentToken == "==") {
            tokenType = EQUALS_EQUALS;
        }
        else if (currentToken == "!=") {
            tokenType = BANG_EQUALS;
        }
        else if (currentToken == "<=") {
            tokenType = L_ANGLE_EQUALS;
        }
        else if (currentToken == ">=") {
            tokenType = R_ANGLE_EQUALS;
        }
        // Handle literal types using regex only where needed
        else if (regex_match(currentToken, regex("(-)?\\d+(\\.\\d*)?([eE][+-]?\\d+)?([fFlLDd]?)"))) {
            tokenType = NUMBER_LITERAL;
        }
        else if (regex_match(currentToken, regex("^0[xX][0-9a-fA-F]+(\\.[0-9a-fA-F]+)?([pP][+-]?\\d+)?$"))) {
            tokenType = HEX_LITERAL;
        }
        else if (regex_match(currentToken, regex("^\"([^\\" "\\]*(\\\\.[^\\" "\\]*)*)\"$"))) {
            tokenType = STRING_LITERAL;
        }
        else if (regex_match(currentToken, regex("true|false"))) {
            tokenType = BOOLEAN_LITERAL;
        }
        // Handle keywords
        else if (currentToken == "abstract") {
            tokenType = KEYWORD_ABSTRACT;
        }
        else if (currentToken == "assert") {
            tokenType = KEYWORD_ASSERT;
        }
        else if (currentToken == "break") {
            tokenType = KEYWORD_BREAK;
        }
        else if (currentToken == "case") {
            tokenType = KEYWORD_CASE;
        }
        else if (currentToken == "catch") {
            tokenType = KEYWORD_CATCH;
        }
        else if (currentToken == "class") {
            tokenType = KEYWORD_CLASS;
        }
        else if (currentToken == "closure") {
            tokenType = KEYWORD_CLOSURE;
        }
        else if (currentToken == "continue") {
            tokenType = KEYWORD_CONTINUE;
        }
        else if (currentToken == "default") {
            tokenType = KEYWORD_DEFAULT;
        }
        else if (currentToken == "do") {
            tokenType = KEYWORD_DO;
        }
        else if (currentToken == "else") {
            tokenType = KEYWORD_ELSE;
        }
        else if (currentToken == "enum") {
            tokenType = KEYWORD_ENUM;
        }
        else if (currentToken == "extends") {
            tokenType = KEYWORD_EXTENDS;
        }
        else if (currentToken == "final") {
            tokenType = KEYWORD_FINAL;
        }
        else if (currentToken == "finally") {
            tokenType = KEYWORD_FINALLY;
        }
        else if (currentToken == "for") {
            tokenType = KEYWORD_FOR;
        }
        else if (currentToken == "if") {
            tokenType = KEYWORD_IF;
        }
        else if (currentToken == "implements") {
            tokenType = KEYWORD_IMPLEMENTS;
        }
        else if (currentToken == "import") {
            tokenType = KEYWORD_IMPORT;
        }
        else if (currentToken == "isoftype") {
            tokenType = KEYWORD_ISOFTYPE;
        }
        else if (currentToken == "interface") {
            tokenType = KEYWORD_INTERFACE;
        }
        else if (currentToken == "module") {
            tokenType = KEYWORD_MODULE;
        }
        else if (currentToken == "native") {
            tokenType = KEYWORD_NATIVE;
        }
        else if (currentToken == "new") {
            tokenType = KEYWORD_NEW;
        }
        else if (currentToken == "nonsealed") {
            tokenType = KEYWORD_NONSEALED;
        }
        else if (currentToken == "permits") {
            tokenType = KEYWORD_PERMITS;
        }
        else if (currentToken == "private") {
            tokenType = KEYWORD_PRIVATE;
        }
        else if (currentToken == "protected") {
            tokenType = KEYWORD_PROTECTED;
        }
        else if (currentToken == "public") {
            tokenType = KEYWORD_PUBLIC;
        }
        else if (currentToken == "return") {
            tokenType = KEYWORD_RETURN;
        }
        else if (currentToken == "sealed") {
            tokenType = KEYWORD_SEALED;
        }
        else if (currentToken == "static") {
            tokenType = KEYWORD_STATIC;
        }
        else if (currentToken == "super") {
            tokenType = KEYWORD_SUPER;
        }
        else if (currentToken == "switch") {
            tokenType = KEYWORD_SWITCH;
        }
        else if (currentToken == "this") {
            tokenType = KEYWORD_THIS;
        }
        else if (currentToken == "throw") {
            tokenType = KEYWORD_THROW;
        }
        else if (currentToken == "throws") {
            tokenType = KEYWORD_THROWS;
        }
        else if (currentToken == "try") {
            tokenType = KEYWORD_TRY;
        }
        else if (currentToken == "void") {
            tokenType = KEYWORD_VOID;
        }
        else if (currentToken == "while") {
            tokenType = KEYWORD_WHILE;
        }
        else if (currentToken == "operator") {
            tokenType = KEYWORD_OPERATOR;
        }
        else if (currentToken == "requires") {
            tokenType = KEYWORD_REQUIRES;
        }
        else if (currentToken == "exports") {
            tokenType = KEYWORD_EXPORTS;
        }
        else if (currentToken == "in") {
            tokenType = KEYWORD_IN;
        }
        else if (currentToken == "global") {
            tokenType = KEYWORD_GLOBAL;
        }

        // Handle primitive types
        else if (currentToken == "bool" || currentToken == "byte" || currentToken == "char" ||
            currentToken == "double" || currentToken == "float" || currentToken == "fraction" ||
            currentToken == "int" || currentToken == "long" || currentToken == "short" ||
            currentToken == "string") {
                tokenType = PRIMITIVE_TYPE;
        }

        else if (regex_match(currentToken, regex("[a-zA-Z_][a-zA-Z0-9_]*$"))) {
            tokenType = IDENTIFIER;
        }
        // If no match, mark as ERROR and log
        if (tokenType == ERROR) {
            cerr << "Lexical error at line " << lineNum << " and column " << columnNum << endl;
        }

        // Create the token and add it to the stack
        if (tokenType != WHITESPACE_MARKER)
            createToken(lineNum, columnNum, tokenType, currentToken, tokenStack);
    }

}


