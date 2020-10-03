#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "lex.h"

using std::ostream;
using std::string;
using std::vector;

ostream& operator<<(ostream& os, const Token& token) {
	static const string tokenTypeNames[] = {"Empty", "Word", "Modifier"};
	const char fill = ' ';
	const int width = 10;
	return os << std::left <<  std::setw(width) << std::setfill(fill) << tokenTypeNames[(int)token.type]
		<< token.value;
}

bool isWordChar(char ch) {
	return isalnum(ch) || ispunct(ch) ||
		ch == '-' || ch == '_';
}

vector<Token> lex(string input) {
	vector<Token> tokens;
	Token currentToken;

	auto pushToken = [&]() {
		if (currentToken.isEmpty())
			return false;
		tokens.push_back(currentToken);
		currentToken = Token();
		return true;
	};

	for (char ch : input) {
		if (ch == ' ') {
			pushToken();
		} else if (ch == '>' || ch == '<' || ch == '&') {
			if (!currentToken.isModifier()) {
				pushToken();
				currentToken.type = modifierT;
			}
			currentToken.value.push_back(ch);
		} else if (isWordChar(ch)) {
			if (!currentToken.isWord()) {
				pushToken();
				currentToken.type = wordT;
			}
			currentToken.value.push_back(ch);
		}
	}
	pushToken();

	return tokens;
}

// https://stackoverflow.com/questions/15598878/posix-sh-ebnf-grammar
// https://github.com/jalanb/jab/blob/__main__/src/bash/bash.bnf
