/*
    ModuleEngine.hh - Definitions for module engine
*/
#pragma once

#include "Module.hh"
#include <functional>
#include <vector>
#include <map>
namespace Mt {
    namespace core {
        typedef Mt::Module* create_t;
        typedef void destroy_t(Mt::Module*);
        /*! \class ModuleEngine
            \brief Mt Module Management

            This class manages the loading, unloading, and references to all Mt::Module instances
            that are loaded.
        */
        class ModuleEngine {
            private:
                /*! \struct mheodule_t
                    \brief Internal Module Type

                    This structure holds the information needed to interact with the loaded module
                */
                typedef struct module_t {
                    // Pointer to the module in memory
                    Module* modulePtr;
                    // Module destructor
                    void (*ModuleDtor)(Module*);
                    // Module handle (for loading / unloading)
                    void * ModuleHandle;
                    std::map<std::string, std::function<void(void *, ...)>> Functions;
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

            public:
                /*!
                    Returns an instance of the module engine
                */
                static ModuleEngine* GetInstance(void);
        };
    }
}
