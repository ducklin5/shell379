/*
 *  */
#include "fragment.h"
#include "../builtins/builtin_manager.h"
#include "../process_table/process_table.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include <iostream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

SimpleCommand::SimpleCommand(string cmdName, vector<string> args,
			     vector<string> inputs, vector<string> outputs,

			     bool background = false)
    : cmdName(cmdName),
      args(args),
      inputs(inputs),
      outputs(outputs),
      background(background) {}

int SimpleCommand::openRedirectFiles() {
	// TODO: multiple outputs and inputs
	stdInBackup = dup(STDIN_FILENO);
	stdOutBackup = dup(STDOUT_FILENO);
	
	// replace stdin with inputs
	for (string input : inputs) {
		close(STDIN_FILENO);
		if (open(input.c_str(), O_RDONLY) < 0) {
			cout << "shell379: failed to open an input "
				"file with errno: "
			     << errno << "\n";
			return errno;
		}
	}

	// replace stdout with outputs
	const int flags = O_CREAT | O_WRONLY | O_TRUNC;
	for (string output : outputs) {
		close(STDOUT_FILENO);
		if (open(output.c_str(), flags, S_IRWXU) < 0) {
			cout << "shell379: failed to open an output "
				"file with errno: "
			     << errno << "\n";
			return errno;
		}
	}
	return 0;
}

void SimpleCommand::restoreStd() {
	dup2(stdInBackup, STDIN_FILENO);
	dup2(stdOutBackup, STDOUT_FILENO);
}

int SimpleCommand::tryBuiltin(bool& found) {
	Builtin* builtin = BuiltinManager::find(cmdName);
	found = builtin != nullptr;
	if (found) {
		return builtin->exec(args);
	}
	return -1;
}

string SimpleCommand::commandString() {
	string command = "";
	command += cmdName;
	for(auto arg: args) command += " " + arg;
	for(auto input: inputs) command += " <" + input;
	for(auto output: outputs) command += " >" + output;
	command += background ? " &" : "";
	return command;
}

int SimpleCommand::parentExec(int childPid) {
	ProcessTable::addProcess(childPid, commandString(), background);
	
	int status, options = WUNTRACED;
	if (background)
		options |= WNOHANG;
	do {
		waitpid(childPid, &status, options);
	} while (!background && !WIFEXITED(status));

	return WEXITSTATUS(status);
}

int SimpleCommand::childExec() {
	if (background) {
		bool found;
		int result = tryBuiltin(found);
		if (found) {
			result == 0 ? exit(EXIT_SUCCESS) :
				exit(EXIT_FAILURE);
		}
	}

	char* execArgs[args.size() + 2];

	// construct char* execArgs
	{
		int i = 0;
		execArgs[i] = strdup(cmdName.c_str());
		for (; i < (int) args.size(); i++) {
			execArgs[i + 1] = strdup(args[i].c_str());
		}
		execArgs[++i] = NULL;
	}

	// execute
	execvp(execArgs[0], execArgs);

	// TODO: send error back to parent with pipes
	cout << "shell379: exec failed with errno: " << errno << "\n";
	exit(EXIT_FAILURE);
}



int SimpleCommand::execute() {
	// try open files now because forking is expensive
	int result = openRedirectFiles();
	if (result != 0) return result;
	
	// no fork case: foreground builtins
	if(!background){
		bool found;
		result = tryBuiltin(found);
		if (found) {
			restoreStd();
			return result;
		}
	}


	signal(SIGCHLD,SIG_IGN);
	// Fork
	int childPid = fork();

	// Child
	if (childPid == 0) {
		return childExec();
	}

	// Parent
	restoreStd();
	if (childPid > 0) {
		return parentExec(childPid);
	} else {
		cout << "fork failed with errno: " << errno;
		return errno;
	}

	return 0;
}
