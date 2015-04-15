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
			this->driver = new Mt::core::lang::SMLDriver(this->ASTBlock);
		}
		REPL::~REPL(void) {
			// Clean up this mish mash.
			if(this->driver != nullptr)
				delete this->driver;
			// This tends to explode every thing. whoops
			//if(this->ASTBlock != nullptr)
			//	delete this->ASTBlock;

		}

		void REPL::ProcessCommand(std::string command) {
			// Simpler than ^C just a normal exit command
			if(command == "exit") {
				this->running = false;
			}
			
			else if (command == "help"){
				std::cout << "exit     - it gets you out" << std::endl;
#if defined(_DEBUG) || defined(DEBUG) 
				std::cout << "dbg-sml  - toggles SML debugging" << std::endl;
				std::cout << "dump-gst - prints out the GST" << std::endl;
#endif
			}
#if defined(_DEBUG) || defined(DEBUG)
			else if (command == "dbg-sml") {
				//  Toggle the SML debugging
				this->driver->ToggleTracing();
				this->eengine.ToggleDebug();
				std::cout << "SML debug tracing toggled (" << std::boolalpha << this->driver->GetIfTracing() << ")" << std::endl;
			} else if (command == "dump-gst") {
				// Helpful during debugging to see what is in the GST
				if(this->GlobalSymbolTable.size() != 0) {
					for (auto& kvp : this->GlobalSymbolTable ) {
						std::cout << kvp.first << " := " << kvp.second << std::endl;
					}
					std::cout << std::endl;
				} else {
					std::cout << "GST EMPTY" << std::endl;
				}
			}
#endif
			else {
				std::cout << "Unknown command '" << command << "'" << std::endl;
			}
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
				// If the line starts with a ! then it is an internal system command, don't pass it on.
				if(strBuffLine[0] == '!') {
					// Pass on the command minus the bang
					this->ProcessCommand(strBuffLine.substr(1));
					// purge the buffer, this allows for us to skip over eval
					strBuffLine.clear();
				}
				// Check to see if the line is empty
				if(!strBuffLine.empty()) {
					// If not, try to parse the line
					if(this->driver->ParseString(strBuffLine, "Mt REPL")) {
						// Lets set the current AST ptr to the new one.
						this->ASTBlock = driver->nblk;
						// Evaluate the current AST
						this->eengine.Evaluate(this->ASTBlock, this->GlobalSymbolTable, strBuffLine);
					}	
				}	
			}
		}
#endif
	}
}
