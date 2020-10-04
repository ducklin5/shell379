#include "builtin_manager.h"

using std::string;
using std::vector;

struct SuspendBuiltin : Builtin {
	public:
	int exec(vector<string> args) override {
		exit(EXIT_SUCCESS);
	}
};
namespace {
	BuiltinManager::Entry entry("suspend", new SuspendBuiltin());
}
