#include "lex.h"
#include "fragment.h"
#include "parser.h"

#include <iostream>

using std::string;
using std::vector;
using std::cout;

Parser::Parser() {}

Parser::~Parser() { delete currentFragment; }

Token Parser::currentToken() {
	if (_currentToken >= (int)tokens.size() || _currentToken < 0)
		throw "Parser: Invalid syntax";
	return tokens[_currentToken];
}

Token Parser::useCurrentToken(TokenType expected) {
	Token current;
	if (currentToken().type == expected) {
		current = currentToken();
		_currentToken++;
	} else {
		throw "Parser: Invalid syntax";
	}
	return current;
}

bool Parser::endOfTokens() { return _currentToken >= (int)tokens.size(); }

Fragment* Parser::trySimpleCommand() {
	if (!currentToken().isWord()) {
		return nullptr;
	}
	string cmdName = useCurrentToken(wordT).value;
	vector<string> args;
	vector<string> inputs;
	vector<string> outputs;
	bool background = false;

	while (!endOfTokens()) {

		if (currentToken().type == wordT) {
			args.push_back(useCurrentToken(wordT).value);

		} else if (currentToken().type == modifierT) {
			string modifier = useCurrentToken(modifierT).value;

			if (modifier == "&") {
				background = true;
				break;
			}

			if (modifier == "<") {
				inputs.push_back(useCurrentToken(wordT).value);
			} else if (modifier== ">" ) {
				outputs.push_back(useCurrentToken(wordT).value);
			}
		}
	}

	return new SimpleCommand(cmdName, args, inputs, outputs, background);
};

Fragment* Parser::parse(string command) {
	tokens = lex(command);
	_currentToken = 0;
	delete currentFragment;

	return trySimpleCommand();
}
