#pragma once
#include <string>

#include "fragment.h"
#include "lex.h"

class Parser {
	std::vector<Token> tokens;
	int _currentToken = 0;
	Fragment* currentFragment = nullptr;

       public:
	Parser();
	~Parser();

       private:
	Token currentToken();

	bool endOfTokens();

	Token useCurrentToken(TokenType expected);
	// tries to parse SimpleCommand Fragment
	// but only if the token sequences pass
	// otherwise returns a nullPtr
	Fragment* trySimpleCommand();

	// tries to parse a Pipe Fragment
	Fragment* tryPipe();

       public:
	Fragment* parse(std::string command);
};

static Parser GlobalParser;
// https://ruslanspivak.com/lsbasi-part7/
// https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_10
