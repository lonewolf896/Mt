/*
	REPL.hh - Mt Read Eval Print Loop implementation
*/
	
#pragma once

#include <iostream>
#include <string>
#include <map>
#include <FlexLexer.h>

#include "core/IMtObject.hh"
#include "third_party/linenoise.hh"
#define _DUMMY_REPL

namespace Mt {
	namespace frontend {
		/*! \class REPL
			\brief Mt Interpreter frontend

			\todo Rewrite linenoise in C++
		*/
		class REPL {
			private:
				// Stores internal and module functions
				//std::map<std::string,std::function<Mt::core::IMtObject(Mt::core::IMtObject obj...)>> GlobalFunctionTable;
				// Stores the current list of symbols for this session
				std::map<std::string, Mt::core::IMtObject> GlobalSymbolTable;

				unsigned int LineNum;
#if !defined(_DUMMY_REPL)
				char* line;
#else
				std::string line;
#endif
			public:
				REPL(void);
				~REPL(void);

				void Start(void);

		};
	}
}
