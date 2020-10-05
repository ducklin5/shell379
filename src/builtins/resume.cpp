#include <signal.h>
#include <sys/types.h>
#include <iostream>

#include "builtin_manager.h"

using std::string;
using std::vector;
using std::cout;

struct ResumeBuiltin : Builtin {
	int exec(vector<string> args) override {
		if(args.size() < 1) {
			cout << "shell379: resume builtin: missing argument\n";
			return 1;
		}
		
		char* p;
		unsigned int pid = (unsigned int) strtol(args[0].c_str(), &p, 10);
    	if(*p) {
			cout << "shell379: resume builtin: argument not a number\n";
			return 2;
		}
		

		if (kill(pid, SIGCONT) < 0) {
			cout << "shell379: resume builtin: failed to resume "
				<< pid << " with errno: "
				<< errno << "\n";
			return errno;
		}
		return 0;
	}

};
namespace {
	BuiltinManager::Entry entry("resume", new ResumeBuiltin());
}
