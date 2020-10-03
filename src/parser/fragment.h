// Smallest individual executable part of a command
#pragma once
#include <string>
#include <vector>

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

	public:
	SimpleCommand(std::string cmdName, std::vector<std::string> args,
			std::vector<std::string> outputs, std::vector<std::string> inputs,
			bool background);
	~SimpleCommand() {}
	
	private:
	int childExec();
	
	int parentExec(int parentExec);

	public:
	int execute() override;
};


class Pipe : public Fragment {};


