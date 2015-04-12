/*
	REPL.cc - Mt Read Eval Print Loop implementation
*/
#include "frontend/REPL.hh"

namespace Mt {
	namespace frontend {
		REPL::REPL(void) {
			// set the initial line number.
			this->LineNum = 0;
			// create a new language driver
			this->driver = new Mt::core::lang::SMLDriver(&(this->ASTBlock));
		}
		REPL::~REPL(void) {
			// Clean up
			delete this->driver;
		}
#if !defined(_DUMMY_REPL)
		// Fancy REPL stuff, 100% broken
		void REPL::Start(void) {
			while((this->line = linenoise("mt> ")) != NULL) {
				std::cout << " " << this->line << std::endl;
				free(this->line);
			}
		}
#else
		void REPL::Start(void) { 
			// current line buffer
			std::string strBuffLine;
			// loop forever!
			while(true) {
				// Print the prompt in the form of mt:#> 
				std::cout << "mt:" << this->LineNum++ << "> ";
				// get the input from cin
				std::getline(std::cin, strBuffLine);
#if !defined(_NOFUN)
				// just a fun little easter egg
				if(strBuffLine == "make") {
					std::cout << "No no Trevor." << std::endl;
					// clear the string so we dont shove this into the eval
					strBuffLine.clear();
				}
#endif	
				// Check to see if the line is empty
				if(!strBuffLine.empty()) {
					// If not, is the contents of the line "dbg"
					if(strBuffLine == "dbg") {
						// if so, toggle the debug values
						driver->trace_scanning = !(driver->trace_scanning);
						driver->trace_parsing = !(driver->trace_parsing);
						std::cout << "Scanner parser debug tracing toggled (" << std::boolalpha << driver->trace_parsing << ")" << std::endl;
					} else {
						// If not, try to parse the line
						if(driver->parse_string(strBuffLine, "Mt REPL")) {
							//driver->eval();
							std::cout << driver->nblk->Count() << std::endl;
						} else {
							// If not, complain loudly
							std::cerr << "Failed to parse SML expression" << std::endl;
						}
						// After all is said and done, echo the input back out
						std::cout << " " << strBuffLine << std::endl;
					}
				}	
			}
		}
#endif
	}
}
