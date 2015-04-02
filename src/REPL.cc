/*
	REPL.cc - Mt Read Eval Print Loop implementation
*/
#include "frontend/REPL.hh"

namespace Mt {
	namespace frontend {
		REPL::REPL(void) {
			this->LineNum = 0;
		}
		REPL::~REPL(void) {

		}
#if !defined(_DUMMY_REPL)
		void REPL::Start(void) {
			while((this->line = linenoise("mt> ")) != NULL) {
				std::cout << " " << this->line << std::endl;
				free(this->line);
			}
		}
#else
		void REPL::Start(void) { 
			std::string strBuffLine;
			while(true) {
				std::cout << "mt:" << this->LineNum++ << "> ";	
				std::getline(std::cin, strBuffLine);
				std::cout << " " << strBuffLine << std::endl;
			}	
		}
#endif
	}
}
