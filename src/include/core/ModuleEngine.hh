/*
    ModuleEngine.hh - Definitions for module engine
*/
#pragma once

#include "Module.hh"

namespace Mt {
    typedef Mt::Module* create_t;
    typedef void destroy_t(Mt::Module*);
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
