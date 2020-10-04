// Smallest individual executable part of a command
#pragma once
#include <string>
#include <vector>

#include "../builtins/builtin.h"

class Fragment {
	public:
	virtual ~Fragment(){}
	virtual int execute() = 0;
};

class SimpleCommand : public Fragment {
	std::string cmdName;
	std::vector<std::string> args;
	std::vector<std::string> inputs;
	std::vector<std::string> outputs;
	bool background;
	
	int stdInBackup, stdOutBackup;
	Builtin* builtin;

	public:
	SimpleCommand(std::string cmdName, std::vector<std::string> args,
			std::vector<std::string> inputs, std::vector<std::string> outputs,
			bool background);
	~SimpleCommand() {}
	
	private:
	int openRedirectFiles();
	void restoreStd();
	int tryBuiltin(bool& found);
	std::string commandString();
	int parentExec(int parentExec);
	int childExec();

	public:
	int execute() override;
};


class Pipe : public Fragment {};


