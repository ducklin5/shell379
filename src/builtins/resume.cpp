#include "builtin_manager.h"

using std::string;
using std::vector;

struct ResumeBuiltin : Builtin {
	int exec(vector<string> args) override {
		exit(EXIT_SUCCESS);
	}
};
namespace {
	BuiltinManager::Entry entry("resume", new ResumeBuiltin());
}
