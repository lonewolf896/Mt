/*
	SMLDriver.cc - Flex and bison driver for SML
*/
#include "core/lang/SMLDriver.hh"

namespace Mt {
	namespace core {
		namespace lang {
			SMLDriver::SMLDriver(Mt::core::lang::NBlock& block) : trace_scanning(false),
																  trace_parsing(false) {

			}

			bool SMLDriver::parse_stream(std::istream& in, const std::string& sname) {
				// Set the stream name
				this->streamname = sname;

				// create a new scanner.
				SMLScanner scanner(&in);
				scanner.set_debug(this->trace_parsing);
				this->lexer = &scanner;

				yy::SMLParser parser(*this);
				parser.set_debug_level(this->trace_parsing);
				return (parser.parse() == 0);
			}

			bool SMLDriver::parse_string(const std::string& input, const std::string& sname) {
				std::istringstream iss(input);
				return this->parse_stream(iss, sname);
			}

			bool SMLDriver::parse_file(const std::strin& filename) {
				std::ifstream in(filename.c_str());
				if(!in.good()) return false;
				return this->parse_stream(in, filename);
			}

			void SMLDriver::error(const class location& l, const std::string& m) {
				std::cerr << l <<": " << m << std::endl;
			}

			void SMLDriver::error(const std::string& m) {
				std::cerr << m << std::endl;
			}

		}
	}
}
