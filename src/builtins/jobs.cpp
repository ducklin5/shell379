#include <sys/resource.h>
#include <sys/time.h>

#include <iomanip>
#include <iostream>

#include "table.h"
#include "builtin_manager.h"
#include "../process_table/process_table.h"

using std::cout;
using std::string;
using std::vector;

struct JobsBuiltin : Builtin {
       private:
	void printRunning(){
		cout << "\nRunning Processes: \n";
		
		int procCount = ProcessTable::getSize();
		if(procCount > 0){
			vector<int> width {2, 6, 2, 5, 30};
			vector<int> align {1, 1, 1, 1, 0};
			Table pTable(5, width, align);
			vector<string> title{"#", "PID", "S", "SEC", "COMMAND"};
			pTable.printRow(title);
		}

		vector<int> width {4, 2, 5, 30};
		vector<int> align {1, 1, 1, 0};
		Table pTable(4, width, align);
		
		string procCountString = std::to_string(procCount);
		vector<string> procCountRow
			{"Processes", "=", procCountString, " active"};
		pTable.printRow(procCountRow);
	}

	void printCompleted() {
		struct rusage usage;
		getrusage(RUSAGE_CHILDREN, &usage);
		string usrTime = std::to_string(usage.ru_utime.tv_sec);
		string sysTime = std::to_string(usage.ru_stime.tv_sec);
		
		cout << "Completed Processes:\n";
		
		vector<int> width {4, 5, 2, 5, 30};
		vector<int> align {1, 1, 1, 1, 0};
		Table pTable(5, width, align);
		
		vector<string> usrTimeRow 
			{"User", "time", "=", usrTime, " seconds" };
		pTable.printRow(usrTimeRow);
		
		vector<string> sysTimeRow 
			{"Sys", "time", "=", sysTime, " seconds" };
		pTable.printRow(sysTimeRow);
	}

	int exec(vector<string> args) override {
		printRunning();
		printCompleted();
		return 0;
	}
};
namespace {
BuiltinManager::Entry entry("jobs", new JobsBuiltin());
}
