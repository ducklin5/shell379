#pragma once
#include <vector>
#include <string>

struct Builtin {
	virtual ~Builtin(){}
	public:
	virtual int exec(std::vector<std::string> args) = 0;
};
