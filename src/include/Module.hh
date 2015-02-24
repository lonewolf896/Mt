/*
	Module.hh - Mt Module interface.
*/

/*
	How to implement a module, the comments guide

	To implement an Mt Module, all you need to do is include this header
	after that, implement the module class, and call the MODULE macro, this
	will make the module visible, there is a disparity between using the built
	in class headers within the module, meaning that there could be an issue with
	resolving the proper methods and such within Mt itself when referencing internal
	types such as Mt::Complex, Mt::Integer, Mt::Double, Mt::Vector, and Mt::Matrix, this
	could be resolved with having all the core types in a libmttypes.so library and then one
	would link to that library as well and then all the types would resolve.
 
*/

#pragma once
/*!
	This macro adds the needed external C calls that Mt needs for loading the module
*/
#define MODULE(MODULE_NAME)								\
extern "C" Mt::Module* InitializeModule(void) {			\
	return Mt::Module::GetInstance();					\
}														\
extern "C" void DeallocateModule(Mt::Module* module) {	\
	delete module;										\
}														\
extern "C" const char * ModuleName(void) {				\
	return MODULE_NAME;									\
}


#include <functional>
#include <map>

namespace Mt { 
	/*! \class Module
		\brief Module for Mt extensibility

		This class contains the header that all Mt modules need to implement in order
		to be considered modules.

		Once a module implements this class, it is required that they call the MODULE macro at 
		the bottom of the implementation source file, as to allow for Mt to properly load the C++ class

	*/
	class Module {
		private:
			/*!
				Pointer for holding a pointer of the current instance of this class as to alow for ease of
				module calling
			*/
			static Module* instance;
			/*!
				Module constructor, only used when Module::GetInstance() is called and should not be used
				manually.
			*/
			Module(void);
		public:
			/*!
				Gets an instance of a module if it is already in memory, if not it constructs one
				and then returns a pointer to the newly constructed instance.
			*/
			static Module* GetInstance(void) {
				if(Module::instance == nullptr)
					Module::instance = new Module();
				return Module::instance;
			}
			/*!
				Module destructor, called prior to module unloading to destroy the created instance 
			*/
			~Module(void);

			void RegisterCommands(std::map<std::string, std::function<void(void *, va_list)>>* FunctionMap);
	};
}
