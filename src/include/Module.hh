/*
    Module.hh - Mt Module interface.
*/
#pragma once

namespace Mt {
    class Module {
        private:
        public:
            Module(void) { }
            virtual ~Module() = 0;
    };
    

    //extern "C" Module* InitializeModule() {
      //  return (new Module());
    //}

    extern "C" void DeallocateModule(Module* module) {
        delete module;
    }
}
