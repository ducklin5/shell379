#include <sys/wait.h>

#include "builtin_manager.h"

using std::string;
using std::vector;
using std::cout;

struct WaitBuiltin : Builtin {
       public:
	int exec(vector<string> args) override {
		if(args.size() < 1) {
			cout << "shell379: wait builtin: missing argument\n";
			return 1;
		}
		
		char* p;
		unsigned int pid = (unsigned int) strtol(args[0].c_str(), &p, 10);
    	if(*p) {
			cout << "shell379: wait builtin: argument not a number\n";
			return 2;
		}
		

		int waitPid, waitPStatus;
		waitPid = waitpid(pid, &waitPStatus, WUNTRACED);
		if (waitPid < 0) {
			cout << "shell379: wait builtin: failed to wait for "
				<< pid << " with errno: "
				<< errno << "\n";
			return errno;
		}
		return 0;
	}
};
namespace {
BuiltinManager::Entry entry("wait", new WaitBuiltin());
}
