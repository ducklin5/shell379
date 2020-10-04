// It uses the factory registration pattern
// This class registers all builtins at runtime
// I could have manually registed all the builtins in this file
// but it seems really ineligant and not scalable
// I can add a whole bunch of builtin cpp files wit

// The c++ implementation was tricky :
// https://stackoverflow.com/questions/11175379/register-a-c-class-so-that-later-a-function-can-iterate-over-all-registered-cl

#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#include "builtin.h"

using BuiltinManagerMap = std::unordered_map<std::string, Builtin*>; 
class BuiltinManager {

	static BuiltinManagerMap& getMap(){
		static BuiltinManagerMap stringBuiltinMap;
		return stringBuiltinMap;
	}
	
	public:
	// TODO: prevent deletion of the return pointer
	static Builtin* find(std::string command) {
		auto temp = getMap();
		auto it = temp.find(command);
		if(it == temp.end()) return nullptr;
		return it->second;
	}

	struct Entry {
		Builtin* instance;
		Entry(std::string command, Builtin* instance): instance(instance) {
			BuiltinManager::getMap()[command] = instance;
		}
		~Entry(){
			delete instance;
		}
	};
	friend struct Entry;
	
};

