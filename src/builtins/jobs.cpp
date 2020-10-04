#include "builtin_manager.h"

using std::string;
using std::vector;

struct JobsBuiltin : Builtin {
	int exec(vector<string> args) override {
		exit(EXIT_SUCCESS);
	}
};
namespace {
	BuiltinManager::Entry entry("jobs", new JobsBuiltin());
}
