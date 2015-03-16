/*
	REPL.hh - Mt Read Eval Print Loop implementation
*/
	
#pragma once

#include <iostream>
#include <string>

#include "third_party/linenoise.hh"

namespace Mt {
	namespace frontend {
		/*! \class REPL
			\brief Mt Interpreter frontend

			\todo Rewrite linenoise in C++
		*/
		class REPL {
			private:
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
