#ifndef LEXER_HPP
#define LEXER_HPP
#include <fstream>
#include "lexeme.hpp"
#include <string>
#include <regex>

extern deque<token> tokenStack;

void scanFile(ifstream& inStream);

deque<string> regex_search_custom(ifstream& file, const regex& pattern);

#endif