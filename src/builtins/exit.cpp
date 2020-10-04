#include "builtin_manager.h"

using std::string;
using std::vector;

struct ExitBuiltin : Builtin {
	int exec(vector<string> args) override {
		exit(EXIT_SUCCESS);
	}
};
namespace {
	BuiltinManager::Entry entry("exit", new ExitBuiltin());
}
