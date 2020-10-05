#include <sys/resource.h>
#include <sys/time.h>

#include <iostream>

#include "builtin_manager.h"
#include "table.h"

using std::string;
using std::vector;
using std::cout;

struct ExitBuiltin : Builtin {
	int exec(vector<string> args) override {
		struct rusage usage;
		getrusage(RUSAGE_SELF, &usage);
		string usrTime = std::to_string(usage.ru_utime.tv_sec);
		string sysTime = std::to_string(usage.ru_stime.tv_sec);

		

		cout << "\nResources Used\n";
		vector<int> width {5, 5, 2, 6, 8};
		vector<int> align {0, 0, 0, 1, 0};
		Table rTable(5, width, align);
		vector<string> usrRow {"User", "time", "=", usrTime, " seconds" };
		rTable.printRow(usrRow);

		vector<string> sysRow {"Sys", "time", "=", sysTime, " seconds" };
		rTable.printRow(sysRow);

		exit(EXIT_SUCCESS);
	}
};
namespace {
	BuiltinManager::Entry entry("exit", new ExitBuiltin());
}
