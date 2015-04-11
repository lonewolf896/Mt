/*
	REPL.cc - Mt Read Eval Print Loop implementation
*/
#include "frontend/REPL.hh"

namespace Mt {
	namespace frontend {
		REPL::REPL(void) {
			this->LineNum = 0;
			this->driver = new Mt::core::lang::SMLDriver(this->ASTBlock);
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
#if !defined(_NOFUN)
				if(strBuffLine == "make") {
					std::cout << "No no Trevor." << std::endl;
				}
#endif
				if(driver->parse_string(strBuffLine)) {
					// Solve AST Here
				} else {
					std::cerr << "Failed to parse SML expression" << std::endl;
				}
				std::cout << " " << strBuffLine << std::endl;
			}	
		}
#endif
	}
}
