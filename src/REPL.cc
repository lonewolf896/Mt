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
			// Clean up this mish mash.
			if(this->driver != nullptr)
				delete this->driver;
			// This tends to explode every thing. whoops
			//if(this->ASTBlock != nullptr)
			//	delete this->ASTBlock;

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
			// Set the running state
			this->running = true;
			// loop forever!
			while(this->running) {
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
				// Simpler than ^C just a normal exit command
				if(strBuffLine == "exit") {
					strBuffLine.clear();
					this->running = false;
				}

				// Check to see if the line is empty
				if(!strBuffLine.empty()) {
					// If not, is the contents of the line "dbg"
					if(strBuffLine == "dbg") {
						// if so, toggle the debug values
						this->driver->ToggleTracing();
						this->eengine.ToggleDebug();
						std::cout << "SML debug tracing toggled (" << std::boolalpha << this->driver->GetIfTracing() << ")" << std::endl;
					} else {
						// If not, try to parse the line
						if(this->driver->ParseString(strBuffLine, "Mt REPL")) {
							// Evaluate the current AST
							this->eengine.Evaluate(&(this->ASTBlock), this->GlobalSymbolTable, strBuffLine);
						}
					}
				}	
			}
		}
#endif
	}
}
