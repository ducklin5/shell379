#pragma once
#include <unordered_map>
#include <string>

using ProcMap = std::unordered_map<int, std::string>;
class ProcessTable {
	static ProcMap& getTable(){
		static ProcMap table = ProcMap();
		return table;
	}
	public:
	static int getSize();
	static int addProcess(int pid, std::string command, bool background);
};
