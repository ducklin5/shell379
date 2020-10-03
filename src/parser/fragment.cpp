#include "fragment.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

SimpleCommand::SimpleCommand(string cmdName, vector<string> args,
			     vector<string> outputs, vector<string> inputs,
			     bool background = false)
    : cmdName(cmdName),
      args(args),
      inputs(inputs),
      outputs(outputs),
      background(background) {}

int SimpleCommand::childExec() {
	char* execArgs[args.size() + 2];
	
	// construct char* execArgs
	{
		int i = 0;
		execArgs[i] = strdup(cmdName.c_str());
		for (; i < args.size(); i++) {
			execArgs[i + 1] = strdup(args[i].c_str());
		}
		execArgs[++i] = NULL;
	}
	
	int result = execvp(execArgs[0], execArgs);

	if (result < 0) {
		cout << "shell379: command not found: " << cmdName;
	}

	return result;
}

int SimpleCommand::parentExec(int childPid) {
	int waitPid, waitPStatus, options = WUNTRACED;

	if (background)
		options |= WNOHANG;

	do {
		waitPid = waitpid(childPid, &waitPStatus, options);

		if (waitPid < 0) {
			perror("waitpid failed");
		}

		if (waitPid == 0) {
			cout << childPid << " is still running";
		}
	} while (waitPid == 0 && !background);
	printf("hello, I am parent of %d (waitPid:%d) (pid:%d)\n", childPid,
	       waitPid, (int)getpid());
	return 0;
}

int SimpleCommand::execute() {
	cout << "Execute: " << cmdName;
	cout << "\nargs: ";
	for (auto arg : args) cout << arg << ", ";
	cout << "\ninput: ";
	for (auto input : inputs) cout << input << ", ";
	cout << "\noutput: ";
	for (auto output : outputs) cout << output << ", ";
	cout << "\nbackground: " << (background ? "yes" : "no");
	cout << "\n--------------------------\n";

	int childPid = fork();
	if (childPid < 0) {
		perror("fork failed");
		exit(EXIT_FAILURE);
	}

	if (childPid == 0) {
		childExec();
	} else {
		parentExec(childPid);
	}

	return 0;
}
