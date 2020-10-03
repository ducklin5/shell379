#include <iostream>

#include "input/input.h"
#include "parser/lex.h"
#include "parser/parser.h"
#include "prompt/prompt.h"

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
		cout << "-----------------------\n";

		for(Token token: lex(inputCommand)) {
			cout << token << "\n";
		}
		
		cout << "-----------------------\n";

		Fragment* command = GlobalParser.parse(inputCommand);
		if (command == nullptr) {
			cout << "Invalid Command\n";
			continue;
		}
		
		command->execute();

		alive = false;
	}

	return 0;
}

// https://unix.stackexchange.com/questions/326626/any-way-to-show-each-step-during-the-command-processing
