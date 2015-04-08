/*
	SMLDriver.hh - Flex and bison driver for SML
*/
#pragma once
#include <istream>
#include <string>

#include "core/lang/ASTObjs.hh"
#include "core/lang/SMLScanner.hh"


namespace Mt {
	namespace core {
		namespace lang {
			/*! \class SMLDriver
				\brief Driver for SML in bison and flex
				
			*/
			class SMLDriver {
			public:
				SMLDriver(Mt::core::lang::NBlock& block);
				bool trace_scanning;
				bool trace_parsing;
				std::string streamname;
				
				/*!
					Invoke the scanner and parser for a stream
					\param[in]	in Input stream
					\param[in]	sname stream name for error messages
					\return 	true if parsing is successful
				*/
				bool parse_stream(std::istream& in, const std::string& sname = "stream input");

				/*!
					Invoke the scanner and parser for a string
					\param[in]	in Input string
					\param[in]	sname stream name for error messages
					\return 	true if parsing is successful
				*/
				bool parse_string(const std::string& input, const std::string& sname = "string stream");

				/*!
					Invoke the SML scanner and parser on a file
					\param[in] filename	Name of the file to parse
					\return		True if parsing is successful
				*/
				bool parse_file(const std::string& filename);

				/*!
					Error handler with location information
					\param[in] l location information
					\param[in] m error message
				*/
				void error(const class location& l, const std::string& m);

				/*!
					General Error handler
					\param[in] m error message
				*/
				void error(const std::string& m);

				class Mt::core::lang::SMLScanner* lexer;
			};
		}
	}
}
