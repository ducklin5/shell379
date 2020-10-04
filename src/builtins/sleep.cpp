#include "builtin_manager.h"
#include <unistd.h>
#include <iostream>

using std::string;
using std::vector;
using std::cout;

struct SleepBuiltin : Builtin {
	public:
	int exec(vector<string> args) override {
		cout << "sleep duration: " << 0 << "\n" << std::flush;
		if(args.size() < 1) {
			cout << "shell379: sleep builtin: missing argument\n";
			return 1;
		}
		
		char* p;
		unsigned int dur = (unsigned int) strtol(args[0].c_str(), &p, 10);
    	if(*p) {
			cout << "shell379: sleep builtin: argument not a number" << args[0] << "\n";
			return 2;
		}
		

		sleep(dur);
		return 0;
	}
};
namespace {
	BuiltinManager::Entry entry("sleep", new SleepBuiltin());
}
