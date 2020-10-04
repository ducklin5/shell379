#pragma once
#include <unordered_map>
#include <string>

class ProcessTable {
	std::unordered_map<int, std::string> table;
	public:
	int addProcess(int pid, std::string command);
	int killProcess(int pid);

};

static ProcessTable GlobalProcessTable;
