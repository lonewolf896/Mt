/*
    ModuleEngine.hh - Definitions for module engine
*/
#pragma once

#include "Module.hh"

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
                typedef struct module_t {
                    Module* modulePtr;
                    void (*ModuleDtor)(Module*);
                    void * ModuleHandle;
                } ModulePackage, *PModulePackage;
                ModuleEngine(void);
                ~ModuleEngine(void);
                static ModuleEngine* instance;

            public:
                static ModuleEngine* GetInstance(void);
        };
    }
}
