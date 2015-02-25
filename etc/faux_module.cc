/*
	faux_module.cc - Example module

	Note: This is the most minimal module example, however, all items here (less the cout) need to be implemented
	to allow for proper function.
*/

// Needed to be an actual module
#include <Module.hh>

#include <iostream>

// Module object is part of the Mt namespace
namespace Mt {
	// Initialize the instance pointer
	Module* Module::instance = nullptr;

	// Implement the constructor
	Module::Module(void) {
		std::cout << "[FAUX_MODULE] I loaded!!!!" << std::endl;
	}

	// Implement the destructor
	Module::~Module(void) {
		std::cout << "[FAUX_MODULE] Unloading!!!!" << std::endl;
	}

	// Implement the register commands call
	void Module::RegisterCommands(std::map<std::string, std::function<void(void *, va_list)>>* FunctionMap) {
		std::cout << "[FAUX_MODULE] ...?" << std::endl;
	}
}

// Add the C interface
// NOTE: This needs to be at the top or bottom of the main module file
// AND it needs to be outside of all namespaces. This provides the external C
// Hooks to allow for Mt to load the module using dl.
MODULE("FAUX_MODULE");
