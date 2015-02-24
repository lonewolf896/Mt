#include <Module.hh>
#include <iostream>

namespace Mt {

	Module* Module::instance = nullptr;

	Module::Module(void) {
		// Module Ctor
		std::cout << "I loaded!!!!" << std::endl;
	}

	Module::~Module(void) {
		std::cout << "Unloading!!!!" << std::endl;
	}

	void Module::RegisterCommands(std::map<std::string, std::function<void(void *, va_list)>>* FunctionMap) {
	std::cout << "...?" << std::endl;
	}
}

MODULE("FAUX_MODULE");
