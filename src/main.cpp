#include <iostream>

#include "input/input.h"
#include "prompt/prompt.h"

using std::cout;
using std::string;

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
		
		cout << "\n" << inputCommand;

		alive = false;
	}

	return 0;
}
