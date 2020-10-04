#include "builtin_manager.h"

using std::string;
using std::vector;

struct KillBuiltin : Builtin {
	int exec(vector<string> args) override {
		exit(EXIT_SUCCESS);
	}
};
namespace {
	BuiltinManager::Entry entry("kill", new KillBuiltin());
}
