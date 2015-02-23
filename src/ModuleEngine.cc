/*
    ModuleEngine.cc - Module Engine implementation
*/
#include "core/ModuleEngine.hh"

namespace Mt {
    namespace core {
        ModuleEngine* ModuleEngine::instance = nullptr;

        ModuleEngine::ModuleEngine(void) {
            
        }

        ModuleEngine::~ModuleEngine(void) {
            this->UnloadAll();
        }

        ModuleEngine* ModuleEngine::GetInstance(void) {
            if (ModuleEngine::instance == nullptr)
                return (ModuleEngine::instance = new ModuleEngine());
            return ModuleEngine::instance;
        }
        // Linux implementation
#if defined(__linux__)
        bool ModuleEngine::LoadModule(std::string module) {
            //ModulePackage *mdl = new  ModulePackage;
            return true;
        }

        bool ModuleEngine::UnloadModule(std::string module) {


        }

        bool ModuleEngine::LoadAll(std::string directory) {
#if defined(DEBUG) | defined(_DEBUG)
            std::cout << "Attempting to load modules from '" << directory << "'" << std::endl;
#endif
            std::vector<std::string> files;
            // If we get an error, pop out.
            if(!this->__LX_GetDirContent(directory, files)) return false;
            // Iterate over all of the files
#if defined(DEBUG) | defined(_DEBUG)
            std::cout << "Found " << files.size() << " modules" << std::endl << std::endl;
#endif

            // Ungodly amount of allocation happens here
            // ~140 TB of ram was attempted to be allocated.
            for(auto module : files){
                // Try to load the module, if not bail out.
                if(!this->LoadModule(module)) return false;
                std::cout << module << std::endl;
            }
            return true;
        }

        bool ModuleEngine::UnloadAll(void) {
            // Perform unloading
            for(auto mod : this->Modules) {

            }
        }
        // Windows implementation
#elif defined(_WIN32)
        bool ModuleEngine::LoadModule(std::string module) {
            
        }

        bool ModuleEngine::UnloadModule(std::string module) {


        }

        bool ModuleEngine::LoadAll(std::string directory) {

        }

        bool ModuleEngine::UnloadAll(void) {


        }
#endif


#if defined(__linux__)
        bool ModuleEngine::__LX_GetDirContent(std::string directory, std::vector<std::string> &files) {
            DIR *dp;
            struct dirent *dirp;
            if((dp  = opendir(directory.c_str())) == NULL) {
                std::cout << "Error: Unable to open '" << directory << "'. Does it exist? (" << errno << ") " << strerror(errno) << std::endl;
                return false;
            }

            while ((dirp = readdir(dp)) != NULL) {
                if(!strncmp(dirp->d_name,".",1) || !strncmp(dirp->d_name, "..", 2))
                    files.push_back(std::string(dirp->d_name));
            }
            closedir(dp);
            return true;
        }
#endif
    }
}
