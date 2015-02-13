/*
    Module.hh - Mt Module interface.
*/

/*
    How to implement a module, the comments guide

    To implement an Mt Module, all you need to do is include this header
    after that, implement the module class, and call the MODULE macro, this
    will make the module visable, there is a disparity between using the built
    in class headers within the module, meaning that there could be an issue with
    resolving the proper methods and such within Mt itself when referencing internal
    types such as Mt::Complex, Mt::Integer, Mt::Double, Mt::Vector, and Mt::Matrix, this
    could be resolved with having all the core types in a libmttypes.so library and then one
    would link to that library as well and then all the types would resolve.
 
*/

#pragma once
// Macro to make the module a visable module,
#define MODULE(MODULE_NAME)                            \
extern "C" Mt::Module* InitializeModule() {            \
    return Mt::Module::GetInstance;                    \
}                                                      \
extern "C" void DeallocateModule(Mt::Module* module) { \
    delete module;                                     \
}                                                      \
extern "C" const char * ModuleName(void)               \
    return MODULE_NAME;                                \
}

namespace Mt { 
    class Module {
        private:
            static Module* instance;
            Module(void) { } 
        public:
            static Module* GetInstance(void) {
                if(Module::instance == nullptr)
                    Module::instance = new Module();
                return Module::instance;
            }
            virtual ~Module() = 0;
    };
}
