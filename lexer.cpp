#include <deque>
#include <string>
#include "lexeme.hpp"
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

deque<token> tokenStack;

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
    string operatorPattern = "\\+=|^#.*|\\+|==|\\+\\+|-=|--|!=|\\s|\\(|\\)|\\.\\.\\.|\\.|=|\\*\\*=|\\*\\*|\\*=|\\*|\\/\\=|\\/|:=|:|\\{|\\}|\\|\\||&&|&=|&|\\|=|@|\\|\\^=|\\^|!";
    string identifierPattern = "(?!\\d)(?!_+$)(?!.*__)[a-zA-Z0-9_]+";
    string whiteSpacePattern = "\\s";
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
        // Classify the token by matching the regex
        if (regex_match(currentToken, regex("(-)?\\d+(\\.\\d*)?([eE][+-]?\\d+)?([fFlLDd]?)"))) {
            tokenType = NUMBER_LITERAL;
        }
        else if (regex_match(currentToken, regex("^0[xX][0-9a-fA-F]+(\\.[0-9a-fA-F]+)?([pP][+-]?\\d+)?$"))) {
            tokenType = HEX_LITERAL;
        }
        else if (regex_match(currentToken, regex("^\\\"([^\\" "\\]*(\\\\.[^\\" "\\]*)*)\\\"$"))) {
            tokenType = STRING_LITERAL;
        }
        else if (regex_match(currentToken, regex("\\/\\/.\\*|\\/\\*[\\s\\S]*?\\*\\/"))) {
            tokenType = COMMENT;
        }
        else if (regex_match(currentToken, regex("\\+=|-\\=|\\*=|\\/=|=|:="))) {
            tokenType = ASSIGNMENT_OPERATOR;
        }
        else if (regex_match(currentToken, regex("\\+|\\-|\\*|\\/|\\+\\+|\\-\\-|\\*\\*|:"))) {
            tokenType = ARITHMETIC_OPERATOR;
        }
        else if (regex_match(currentToken, regex("==|!=|<=|>=|<|>"))) {
            tokenType = COMPARISON_OPERATOR;
        }
        else if (regex_match(currentToken, regex("&&|\\|\\|!|\\^\\^"))) {
            tokenType = LOGIC_OPERATOR;
        }
        else if (regex_match(currentToken, regex("&|\\||\\^|<<|>>"))) {
            tokenType = BITWISE_OPERATOR;
        }
        else if (regex_match(currentToken, regex("^#.*$"))) {
            tokenType = MACRO_LINE;
        }
        else if (regex_match(currentToken, regex(("(\\r\\n|\\n|\\r)")))) {
            tokenType = NEWLINE;
            lineNum++;
            columnNum = 1;
        }
        else if (regex_match(currentToken, regex("\\s+"))) {
            tokenType = WHITESPACE_MARKER;
        }
        else if (regex_match(currentToken, regex("[.,;]"))) {
            tokenType = PUNCTUATION;
        }
        else if (regex_match(currentToken, regex("\\("))) {
            tokenType = LEFT_PARENTHESIS;
        }
        else if (regex_match(currentToken, regex("\\)"))) {
            tokenType = RIGHT_PARENTHESIS;
        }
        else if (regex_match(currentToken, regex("\\{"))) {
            tokenType = LEFT_BRACE;
        }
        else if (regex_match(currentToken, regex("\\}"))) {
            tokenType = RIGHT_BRACE;
        }
        else if (regex_match(currentToken, regex("abstract|bool|break|byte|case|catch|char|class|continue|default|do|double|else|enum|extends|final|finally|float|for|if|implements|import|isoftype|int|interface|long|module|native|new|private|protected|public|return|short|static|super|switch|this|throw|throws|true|false|try|void|while|operator|requires|exportsh"))) {
            tokenType = KEYWORD;
        }
        else if (regex_match(currentToken, regex("[a-zA-Z_][a-zA-Z0-9_]*$"))) {
            tokenType = IDENTIFIER;
        }
        else {
            tokenType = ERROR;  // If no match, mark as ERROR
        }


        // Create the token and add it to the stack
        createToken(lineNum, columnNum, tokenType, currentToken, tokenStack);        

    }
}


