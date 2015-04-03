/*
	ModuleEngine.hh - Definitions for module engine
*/
#pragma once

#include "Module.hh"

#if defined(__linux__) | defined(__APPLE__)
#include <dlfcn.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#define M_HANDLE void *
#elif defined(_WIN32)
#include <Windows.h>
#define M_HANDLE HINSTANCE
#endif

#include <algorithm>
#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

namespace Mt {
	namespace core {
		// Constructor type
		typedef Mt::Module* create_t();
		// Destructor type
		typedef void destroy_t(Mt::Module*);
		// Type to get module name
		typedef const char * modulename_t();
		/*! \class ModuleEngine
			\brief Mt Module Management

			This class manages the loading, unloading, and references to all Mt::Module instances
			that are loaded.

			\todo Windows Implementation of module loading etc
		*/
		class ModuleEngine {
			private:
				/*! \struct module_t
					\brief Internal Module Type

					This structure holds the information needed to interact with the loaded module
				*/
				typedef struct module_t {
					// Constructor Handle
					create_t* mdlCtor;
					// Destructor Handle
					destroy_t* mdlDtor;
					// Module handle (for loading / unloading)
					M_HANDLE ModuleHandle;
					// Module name handle
					modulename_t* mdlName;
					// Pointer to the module in memory
					Module* modulePtr;
					// Function Map
					std::map<std::string, std::function<void(void *, va_list)>> Functions;
				} ModulePackage, *PModulePackage;
				/*!
					Internal Constructor, used to setup memory and loading bits
				*/
				ModuleEngine(void);
				/*!
					Internal Destructor, Not used ATM
				*/
				~ModuleEngine(void);
				/*!
					Internal instance of the module engine
				*/
				static ModuleEngine* instance;

				/*!
					Collection of currently loaded modules
				*/
				std::map<std::string, ModulePackage*> Modules;

#if defined(__linux__) | defined(__APPLE__)
				/*!
					Internal Linux implementation to get all files in a given directory
				*/
				bool __LX_GetDirContent(std::string directory, std::vector<std::string> &files);
#elif defined(_WIN32)
				/*!
					Internal Windows implementation to get all files in a given directory
				*/
				bool __WI_GetDirContent(std::string directory, std::vector<std::string> &files);
#endif

				/*!
					Used to filter the input from the directory reading to see if it is a loadable module
				*/
				static bool IsValidModule(std::string ModuleName);
				/*!
					Used by ModuleEngine::IsValidModule to deter min valid modules by the extension
				*/
				static std::string ending;
			public:
				/*!
					Returns an instance of the module engine
				*/
				static ModuleEngine* GetInstance(void);

				/*!
					Loads a module by path and name

					\todo Windows Implementation
				*/
				bool LoadModule(std::string module);

				/*!
					Unloads a module with the given name if found.

					\todo Windows Implementation
				*/
				bool UnloadModule(std::string module);

				/*!
					Loads all modules found in a given directory

					\todo Windows Implementation
				*/
				bool LoadAll(std::string directory);

				/*!
					Unloads all loaded modules

					\todo Windows Implementation
				*/
				bool UnloadAll(void);
		};
	}
}
