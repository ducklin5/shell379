#include <signal.h>
#include <sys/types.h>
#include <iostream>
#include "process_table.h"

using std::cout;


int ProcessTable::getSize() {
	ProcMap table = getTable();
	return table.size();
}

int ProcessTable::addProcess(int pid, std::string command, bool background){
	if(getTable().count(pid) > 0){
		cout << "shell379: process_table: pid exists \n";
		return 1;
	}

	
	if (background)
		cout <<  "{"<< getTable().size() << "}\t"<< pid << "\n";

	getTable()[pid] = command;
	return 0;
}
