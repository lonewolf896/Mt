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
            ModulePackage *mdl = new  ModulePackage;
        }

        bool ModuleEngine::UnloadModule(std::string module) {


        }

        bool ModuleEngine::LoadAll(std::string directory) {
            std::vector<std::string> files;
            // If we get an error, pop out.
            if(!this->__LX_GetDirContent(directory.c_str(), files)) return false;
            // Iterate over all of the files
            for(std::string module : files){
                // Try to load the module, if not bail out.
                if(!this->LoadModule(module)) return false;
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
        bool ModuleEngine::__LX_GetDirContent(const char * directory, std::vector<std::string> &files) {
#if defined(_DEBUG) | defined(DEBUG)
            std::cout << "Attempting to load modules from '" << directory << "'" << std::endl;
#endif
            DIR *dp;
            struct dirent *dirp;
            if((dp  = opendir(directory)) == NULL) {
                std::cout << "Error: Unable to open '" << directory << "'. Does it exist? (" << errno << ") " << strerror(errno) << std::endl;
                return false;
            }

            while ((dirp = readdir(dp)) != NULL) {
                if(dirp->d_name != "." && dirp->d_name != "..")
                    files.push_back(std::string(dirp->d_name));
            }
            closedir(dp);
            return true;
        }
#endif
    }
}
