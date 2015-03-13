/*
	ModuleEngine.cc - Module Engine implementation
*/
#include "core/ModuleEngine.hh"

namespace Mt {
	namespace core {
		ModuleEngine* ModuleEngine::instance = nullptr;
		// Shut up, I can call the module extension what ever I damn well please.
		// MOdulE - Thats how I'm justifying it.
		std::string ModuleEngine::ending = ".moe";

		ModuleEngine::ModuleEngine(void) {
			// Nothing to do really...
		}

		ModuleEngine::~ModuleEngine(void) {
			this->UnloadAll();
		}

		ModuleEngine* ModuleEngine::GetInstance(void) {
			if (ModuleEngine::instance == nullptr)
				return (ModuleEngine::instance = new ModuleEngine());
			return ModuleEngine::instance;
		}
#if defined(__linux__) | defined(__APPLE__) // *NIX implementation
		bool ModuleEngine::LoadModule(std::string module) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Attempting to load module '" << module << "'" << std::endl;
#endif
			ModulePackage *mdl = new  ModulePackage;
			mdl->ModuleHandle = dlopen(("./"+module).c_str(), RTLD_LAZY);
			if(!mdl->ModuleHandle) {
				std::cout << "Error loading module '" << module << "'. " << dlerror() << std::endl;
				delete mdl;
				return false;
			}
			// Attempt to get the handle of the module constructor C interface
			mdl->mdlCtor =  (create_t*)dlsym(mdl->ModuleHandle, "InitializeModule");
			// Attempt to get the handle for the module destructor C interface
			mdl->mdlDtor = (destroy_t*)dlsym(mdl->ModuleHandle, "DeallocateModule");
			// Attempt to get the handle for the raw name used for namespacing modules
			mdl->mdlName = (modulename_t*)dlsym(mdl->ModuleHandle, "ModuleName");
			if(mdl->mdlDtor == nullptr || mdl->mdlCtor == nullptr || mdl->mdlName == nullptr) {
				// Close the module
				dlclose(mdl->ModuleHandle);
				std::cout << "Error loading module '" << module << "'. I don't have the needed function pointers... " << dlerror() << std::endl;
				delete mdl;
				return false;
			}
			// Attempt to create the module
			mdl->modulePtr = mdl->mdlCtor();
			if(mdl->modulePtr == nullptr) {
				dlclose(mdl->ModuleHandle);
				std::cout << "Error: unable to construct module '" << module << "'" << std::endl;
				delete mdl;
				return false;
			}

#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Loaded '" << module << "'" << std::endl;
#endif
			// That should do it.
			return true;
		}
		// Unloads the module
		bool ModuleEngine::UnloadModule(std::string module) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Unloading '" << module << "'" << std::endl;
#endif
			// Unload the module and reclaim the memory from the module_t
			this->Modules[module]->mdlDtor(this->Modules[module]->modulePtr);
			dlclose(this->Modules[module]->ModuleHandle);
			delete this->Modules[module];
			// Pop the module out of the map
			this->Modules.erase(module);
			// Should have some error catching I suppose but w/e
			return true;
		}

		bool ModuleEngine::LoadAll(std::string directory) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Attempting to load modules from '" << directory << "'" << std::endl;
#endif
			std::vector<std::string> files;
			// If we get an error, pop out.
			if(!this->__LX_GetDirContent(directory, files)) return false;
			
			// Filter out the garbage in the directory
			files.erase(std::remove_if(files.begin(), files.end(), IsValidModule), files.end());
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Found " << files.size() << " modules" << std::endl << std::endl;
#endif
			// Ungodly amount of allocation happens here
			// ~140 TB of ram was attempted to be allocated.
			// Iterate over all of the files
			for(auto& module : files){
				// Try to load the module, if not bail out.
				if(!this->LoadModule(module)) {
					std::cout << "Loading of the module '" << module << "' failed." << std::endl;
					return false;
				}
			}
			return true;
		}

		bool ModuleEngine::UnloadAll(void) {
#if defined(_DEBUG) || defined(DEBUG)
			std::cout << std::endl << "Unloading Modules..." << std::endl;
#endif
			// Perform unloading
			for(auto& mod : this->Modules) {
				// Tell us to unload the module by name
				this->UnloadModule(mod.first);
			}
			return true;
		}
#elif defined(_WIN32) // Windows implementation 
		bool ModuleEngine::LoadModule(std::string module) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Attempting to load module '" << module << "'" << std::endl;
#endif
			ModulePackage *mdl = new  ModulePackage;
			mdl->ModuleHandle = LoadLibrary(("./"+module).c_str());
			if(!mdl->ModuleHandle) {
				std::cout << "Error loading module '" << module << "'. " << dlerror() << std::endl;
				delete mdl;
				return false;
			}
			mdl->mdlCtor =  (create_t*)GetProcAddress(mdl->ModuleHandle, "InitializeModule");
			mdl->mdlDtor = (destroy_t*)GetProcAddress(mdl->ModuleHandle, "DeallocateModule");
			mdl->mdlName = (modulename_t*)GetProcAddress(mdl->ModuleHandle, "ModuleName");
			if(mdl->mdlDtor == nullptr || mdl->mdlCtor == nullptr || mdl->mdlName == nullptr) {
				// Close the module
				FreeLibrary(mdl->ModuleHandle);
				std::cout << "Error loading module '" << module << "'. I don't have the needed function pointers... " << dlerror() << std::endl;
				delete mdl;
				return false;
			}
			mdl->modulePtr = mdl->mdlCtor();
			if(mdl->modulePtr == nullptr) {
				dlclose(mdl->ModuleHandle);
				std::cout << "Error: unable to construct module '" << module << "'" << std::endl;
				delete mdl;
				return false;
			}

#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Loaded '" << module << "'" << std::endl;
#endif
			return true;
		}

		bool ModuleEngine::UnloadModule(std::string module) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Unloading '" << module << "'" << std::endl;
#endif
			this->Modules[module]->mdlDtor(this->Modules[module]->modulePtr);
			FreeLibrary(this->Modules[module]->ModuleHandle);
			delete this->Modules[module];
			this->Modules.erase(module);
			return true;
		}

		bool ModuleEngine::LoadAll(std::string directory) {
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Attempting to load modules from '" << directory << "'" << std::endl;
#endif
			std::vector<std::string> files;
			if(!this->__WI_GetDirContent(directory, files)) return false;
			files.erase(std::remove_if(files.begin(), files.end(), IsValidModule), files.end());
#if defined(DEBUG) | defined(_DEBUG)
			std::cout << "Found " << files.size() << " modules" << std::endl << std::endl;
#endif
			for(auto& module : files){

				if(!this->LoadModule(module)) {
					std::cout << "Loading of the module '" << module << "' failed." << std::endl;
					return false;
				}
			}
			return true;
		}

		bool ModuleEngine::UnloadAll(void) {
#if defined(_DEBUG) || defined(DEBUG)
			std::cout << std::endl << "Unloading Modules..." << std::endl;
#endif
			for(auto& mod : this->Modules) {
				this->UnloadModule(mod.first);
			}
			return true;
		}
#endif


#if defined(__linux__) | defined(__APPLE__)
		bool ModuleEngine::__LX_GetDirContent(std::string directory, std::vector<std::string> &files) {
			// Yay! File-system interaction. 
			DIR *dp;
			struct dirent *dirp;
			if((dp  = opendir(directory.c_str())) == NULL) {
				std::cout << "Error: Unable to open '" << directory << "'. Does it exist? (" << errno << ") " << strerror(errno) << std::endl;
				return false;
			}

			while ((dirp = readdir(dp)) != NULL) {
					files.push_back(std::string(dirp->d_name));
			}
			closedir(dp);
			return true;
		}
#elif defined(_WIN32)
		bool ModuleEngine::__WI_GetDirContent(std::string directory, std::vector<std::string> &files) {
			// TODO :T
		}
#endif

		bool ModuleEngine::IsValidModule(std::string ModuleName) {
			// Check to see if it the symbol for the current directory or the parent
			if(ModuleName == ".." || ModuleName == ".") return true;
			// Check the file extension to see if it is a .moe
			return  (0 != ModuleName.compare(ModuleName.length() - ModuleEngine::ending.length(), ModuleEngine::ending.length(), ModuleEngine::ending));            
		}
	}
}
