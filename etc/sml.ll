/*
	sml.l - Simple Math Language (SML) flex lexer grammar

*/

%option c++
%option prefix="Mt" 
%option noyywrap
%option yylineno 
%option nounput 
%option batch 
%option debug 

%{
	#include <iostream>
	#include <string>

	#include "core/lang/ASTObjs.hh"
	#include "core/lang/SMLDriver.hh"
	#include "core/lang/SMLScanner.hh"
	#include "core/lang/Parser.hh"

	#define SAVE_TOKEN yylval.string = new std::string(yytext, yyleng)
	#define TOKEN(t) (yylval.token = t)

	#define YY_USER_ACTION  yylloc->columns(yyleng);
	
%}

%%

%{
    // reset location
    yylloc->step();
%}

[ \t\n\r]					;
[a-zA-Z_][a-zA-Z0-9_]*	SAVE_TOKEN; return TIDENTIFIER;
[0-9]+\.[0-9]*			SAVE_TOKEN; return TDOUBLE;
[0-9]+					SAVE_TOKEN; return TINTEGER;
\<.+\>\n				SAVE_TOKEN;	return TLIST;
[0-9]+[\+\-][0-9]+i 		SAVE_TOKEN; return TCOMPLEX;

"="						return TOKEN(TEQUAL);
":="					return TOKEN(TASSIGN);
"=="                    return TOKEN(TCEQ);
"+="					return TOKEN(TPEQUAL);
"-="					return TOKEN(TMEQUAL);
"/="					return TOKEN(TDEQUAL);
"*="					return TOKEN(TMUEQUAL);
"%="					return TOKEN(TMOEQUAL);
"!="					return TOKEN(TNEQUAL);
"<"						return TOKEN(TCLT);
"<="					return TOKEN(TCLE);
">"						return TOKEN(TCGT);
">="					return TOKEN(TCGE);
"::"					return TOKEN(TSRO);
"("						return TOKEN(TLPAREN);
")"						return TOKEN(TRPAREN);
"{"                     return TOKEN(TLBRACE);
"}"                     return TOKEN(TRBRACE);
"."						return TOKEN(TDOT);
","						return TOKEN(TCOMMA);
"+"						return TOKEN(TPLUS);
"-"						return TOKEN(TMINUS);
"*"						return TOKEN(TMUL);
"/"						return TOKEN(TDIV);
"%"						return TOKEN(TMOD);
"^"						return TOKEN(TPOW);
"~"                     return TOKEN(TROOT);
.						std::cout << "Error: Unknown Token" << std::endl; yyterminate();

%%

namespace Mt {
	namespace core {
		namespace lang {
			SMLScanner::SMLScanner(std::istream* in, std::ostream* out) : MtFlexLexer(in, out) { }
			SMLScanner::~SMLScanner(void) { }
			SMLScanner::set_debug(bool b) {
				yy_flex_debug = b;
			}
		}
	}
}

#ifdef yylex
#undef yylex
#endif

int MtFlexLexer::yylex(void) {
	std::cerr << "in MtFlexLexer::yylex() !" << std::endl;
    return 0;
}
int MtFlexLexer::yywrap() {
    return 1;
}
