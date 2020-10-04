#include <iostream>

#include "input/input.h"
#include "parser/lex.h"
#include "parser/parser.h"
#include "prompt/prompt.h"

using std::cout;
using std::string;
using std::vector;

int main(int argc, char* argv[]) {
	int returnCode = 0;
	while(true) {
		if (showPrompt() != 0) {
			cout << "\nFailed to show prompt\n";
			return -1;
		}

		string inputCommand;
		int inputResult = InputManager.grabInput(inputCommand);
		if (inputResult != 0) {
			if (inputResult < 0) cout << "\nFailed to get input\n";
			returnCode = inputResult;
			return -1;
		}
	
		Fragment* command = GlobalParser.parse(inputCommand);
		if (command == nullptr){
			continue;
		}
		
		returnCode = command->execute();
	}
	
	// Clean up

	return returnCode;
}

// https://unix.stackexchange.com/questions/326626/any-way-to-show-each-step-during-the-command-processing
