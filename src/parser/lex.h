#pragma once
#include <iostream>
#include <string>
#include <vector>

enum TokenType { emptyT, wordT, modifierT};

struct Token {
	TokenType type;
	std::string value;

	Token() : type(emptyT), value("") {}

	Token(TokenType type, std::string value) : type(type), value(value) {
		if ((int)value.length() == 0)
			type = emptyT;
	}

	bool isEmpty() { return type == emptyT; }

	bool isModifier() { return type == modifierT;}

	bool isWord() { return type == wordT; }
	
	friend std::ostream& operator<<(std::ostream&, const Token&);
};

std::ostream& operator<<(std::ostream& os, const Token& token);

std::vector<Token> lex(std::string input);
