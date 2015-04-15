/*
	sml.l - Simple Math Language (SML) flex lexer grammar

*/

%{
	#ifndef yyterminate
	#define yyterminate() return TOKEN(token::END)
	#endif
	#include "core/lang/SMLScanner.hh"
	typedef yy::SMLParser::token token;
	typedef yy::SMLParser::token_type token_type;
	#define YY_NO_UNISTD_H
	#if defined(__clang__)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wdeprecated-register"
	#pragma clang diagnostic ignored "-Wsign-compare"
	#elif defined(__GCC__)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wdeprecated-register"
	#pragma CGG diagnostic ignored "-Wsign-compare"
	#endif
%}


%option c++
%option yywrap
%option yylineno 
%option nounput 
%option batch 
%option debug
%option stack

%{
	#include <iostream>
	#include <string>

	#include "core/lang/ASTObjs.hh"
	#include "core/lang/SMLDriver.hh"
	
	#include "core/lang/Parser.hh"

	#define SAVE_TOKEN yylval->string = new std::string(yytext, yyleng)
	#define TOKEN(t) static_cast<token_type>((yylval->token = t))

	#define YY_USER_ACTION  yylloc->columns(yyleng);
	
%}

%%

%{
	// reset location
	yylloc->step();
%}

[ \t\r]+				{ yylloc->step(); }
\n 						{ yylloc->lines(yyleng); yylloc->step(); }

[a-zA-Z_][a-zA-Z0-9_]*	SAVE_TOKEN; return token::TIDENTIFIER;
[0-9]+\.[0-9]*			SAVE_TOKEN; return token::TSCALAR;
[0-9]+					SAVE_TOKEN; return token::TSCALAR;
\<.+\>\n				SAVE_TOKEN;	return token::TLIST;
[0-9]+[\+\-][0-9]+i 	SAVE_TOKEN; return token::TCOMPLEX;

"="						return TOKEN(token::TEQUAL);
":="					return TOKEN(token::TASSIGN);
"=="					return TOKEN(token::TCEQ);
"+="					return TOKEN(token::TPEQUAL);
"-="					return TOKEN(token::TMEQUAL);
"/="					return TOKEN(token::TDEQUAL);
"*="					return TOKEN(token::TMUEQUAL);
"%="					return TOKEN(token::TMOEQUAL);
"!="					return TOKEN(token::TNEQUAL);
"<"						return TOKEN(token::TCLT);
"<="					return TOKEN(token::TCLE);
">"						return TOKEN(token::TCGT);
">="					return TOKEN(token::TCGE);
"::"					return TOKEN(token::TSRO);
"("						return TOKEN(token::TLPAREN);
")"						return TOKEN(token::TRPAREN);
"{"						return TOKEN(token::TLBRACE);
"}"						return TOKEN(token::TRBRACE);
"."						return TOKEN(token::TDOT);
","						return TOKEN(token::TCOMMA);
"+"						return TOKEN(token::TPLUS);
"-"						return TOKEN(token::TMINUS);
"*"						return TOKEN(token::TMUL);
"/"						return TOKEN(token::TDIV);
"%"						return TOKEN(token::TMOD);
"^"						return TOKEN(token::TPOW);
"~"						return TOKEN(token::TROOT);
.						std::cout << "Error: Unknown Token \"" <<  yytext << "\"" << std::endl; yyterminate();

%%

namespace Mt {
	namespace core {
		namespace lang {
			SMLScanner::SMLScanner(std::istream* in, std::ostream* out) : yyFlexLexer(in, out) { }
			SMLScanner::~SMLScanner(void) { }
			void SMLScanner::set_debug(bool b) {
				yy_flex_debug = b;
			}
		}
	}
}

#ifdef yylex
#undef yylex
#endif

int yyFlexLexer::yylex(void) {
	std::cerr << "in MtFlexLexer::yylex() !" << std::endl;
	return 0;
}
int yyFlexLexer::yywrap() {
	return 1;
}
#if defined(__clang__)
#pragma clang diagnostic pop
#elif defined(__GCC__)
#pragma GCC diagnostics pop
#endif
