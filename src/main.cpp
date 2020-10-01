#include <iostream>

#include "input/input.h"
#include "prompt/prompt.h"
#include "parser/lex.h"

using std::cout;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {
	bool alive = true;
	while (alive) {
		if (showPrompt() != 0) {
			cout << "\nFailed to show prompt\n";
			return -1;
		}

		string inputCommand;
		if (InputManager.grabInput(inputCommand) != 0) {
			cout << "\nFailed to get input\n";
		}

		
		cout << "\n" << inputCommand << "\n";
		vector<Token> tokens = lex(inputCommand);
		
		for (auto token: tokens) {
			cout << token << "\n";
		}

		alive = false;
	}

	return 0;
}
