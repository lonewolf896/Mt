/*
	SMLDriver.cc - Flex and bison driver for SML
*/
#include "core/lang/SMLDriver.hh"
#include "core/lang/SMLScanner.hh"

namespace Mt {
	namespace core {
		namespace lang {
			// Constructor chaining to make things less repeaty
			SMLDriver::SMLDriver(class Mt::core::lang::NBlock* block) : SMLDriver(block, false) { }
			SMLDriver::SMLDriver(class Mt::core::lang::NBlock* block, bool debug) : 	trace_scanning(debug),
				/*	Oh hi this is a block of useless whitespace that can't be filled */	trace_parsing(debug),
				/*	Sp I'm just going to take up space with a comment, to fill it... */	nblk(block) {
				if(Mt::core::Config::GetInstance()->CfgHasValue("helpful_errors")) {
					if(Mt::core::Config::GetInstance()->GetCfgValue("helpful_errors") == "yes")
						this->helpful_errors = true;
					else
						this->helpful_errors = false;
				} else {
					this->helpful_errors = true;
				}										  						
			}

			bool SMLDriver::ParseStream(std::istream& in, const std::string& sname) {
				// Set the stream name
				this->streamname = sname;

				// create a new scanner.
				SMLScanner scanner(&in);
				scanner.set_debug(this->trace_parsing);
				this->lexer = &scanner;

				// New parser
				yy::SMLParser parser(*this);
				parser.set_debug_level(this->trace_parsing);
				return (parser.parse() == 0);
			}

			bool SMLDriver::ParseString(const std::string& input, const std::string& sname) {
				// Hold onto the string so we can mark down where an error happed
				this->texpr = input;
				std::istringstream iss(input);
				return this->ParseStream(iss, sname);
			}

			bool SMLDriver::ParseFile(const std::string& filename) {
				std::ifstream in;
				in.open(filename.c_str());
				if(!in.good()) return false;
				return this->ParseStream(in, filename);
			}

			void SMLDriver::Error(const yy::location& l, const std::string& m) {
				// Print out the normal error message
				std::cerr << l <<": " << m << std::endl;
				// if we have helpful_errors enabled
				if(this->helpful_errors){
					// print out the expression
					std::cerr << " " << this->texpr << std::endl << " ";
					// get the ending column for the error
					int end_col = 0 < l.end.column ? l.end.column - 1 : 0;
					// fill the space with ~
					for(int i = 0; i < (end_col-1); i++)
						std::cerr << "~";
					// Place a ^ right where the error is
					std::cerr << "^";
					// Fill the rest of the space
					for(int i = (end_col + 1); i < (int)(this->texpr.size())+1; i++)
						std::cerr << "~";
					// New line
					std::cerr << std::endl;
				}
			}

			void SMLDriver::Error(const std::string& m) {
				std::cerr << m << std::endl;
			}

			std::string SMLDriver::GetStreamname(void) {
				return this->streamname;
			}

			void SMLDriver::ToggleTracing(void) {
				this->trace_scanning = !this->trace_scanning;
				this->trace_parsing = !this->trace_parsing;
			}

			bool SMLDriver::GetIfTracing(void) {
				return this->trace_parsing;
			}

			void SMLDriver::ToggleErrorHelp(void) {
				this->helpful_errors = !this->helpful_errors;
			}
		}
	}
}
