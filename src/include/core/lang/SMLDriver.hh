/*
	SMLDriver.hh - Flex and bison driver for SML
*/
#pragma once
#include <sstream>
#include <istream>
#include <fstream>
#include <string>

#include "core/lang/ASTObjs.hh"
#include "core/Config.hh"
#include "location.hh"



namespace Mt {
	namespace core {
		namespace lang {
			class SMLScanner;
			/*! \class SMLDriver
				\brief Driver for SML in bison and flex
				
			*/
			class SMLDriver {
			private:
				std::string texpr;
				bool helpful_errors;
				bool trace_scanning;
				bool trace_parsing;
			public:
				std::string streamname;
				/*!
					Constructs a new instance of the SML driver
					\param[in]	block SML AST Block
				*/
				SMLDriver(class Mt::core::lang::NBlock* block);
				SMLDriver(class Mt::core::lang::NBlock* block, bool debug);
				
				/*!
					Invoke the scanner and parser for a stream
					\param[in]	in Input stream
					\param[in]	sname stream name for error messages
					\return 	true if parsing is successful
				*/
				bool ParseStream(std::istream& in, const std::string& sname = "stream input");

				/*!
					Invoke the scanner and parser for a string
					\param[in]	in Input string
					\param[in]	sname stream name for error messages
					\return 	true if parsing is successful
				*/
				bool ParseString(const std::string& input, const std::string& sname = "string stream");

				/*!
					Invoke the SML scanner and parser on a file
					\param[in] filename	Name of the file to parse
					\return		True if parsing is successful
				*/
				bool ParseFile(const std::string& filename);

				/*!
					Error handler with location information
					\param[in] l location information
					\param[in] m error message
				*/
				void Error(const yy::location& l, const std::string& m);

				/*!
					General Error handler
					\param[in] m error message
				*/
				void Error(const std::string& m);

				/*!
					Returns the name of the current stream
				*/
				std::string GetStreamname(void);

				/*!
					Toggles the parser and scanner tracing flags
				*/
				void ToggleTracing(void);

				/*!
					Returns if the debug tracing for the scanner and parser is on.
				*/
				bool GetIfTracing(void);

				/*!
					Toggles the helpful error messages
				*/
				void ToggleErrorHelp(void);

				/*!
					Pointer to the Lexer Scanner
				*/
				class Mt::core::lang::SMLScanner* lexer;
				/*!
					Pointer to the AST NBlock filed during SML parsing
				*/
				class Mt::core::lang::NBlock* nblk;
			};
		}
	}
}
