/*core
	SMLScanner.hh - Scanner wrapper class
*/
#pragma once
#include "core/lang/Parser.hh"

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL
#define	YY_DECL												\
    Mt::core::lang::SMLParser::token_type					\
    Mt::core::lang::SMLScanner::lex(						\
	Mt::core::lang::SMLParser::semantic_type* yylval,		\
	Mt::core::lang::SMLParser::location_type* yylloc		\
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer MtFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif


namespace Mt {
	namespace core {
		namespace lang {
			/*! \class SMLScanner
				\brief Wrapper for Flex
			*/
			class SMLScanner {
			public:
				SMLScanner(std::istream* arg_yyin = 0, std::ostream* arg_yyout = 0);
				virtual ~SMLScanner(void);
				virtual Mt::core::lang::SMLParser::token_type lex(Mt::core::lang::SMLParser::semantic_type* yylval, Mt::core::lang::SMLParser::location_type* yylloc);
				void set_debug(bool b);
			};
		}
	}
}
