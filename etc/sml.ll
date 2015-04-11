/*
	sml.l - Simple Math Language (SML) flex lexer grammar

*/

%{
	#include "core/lang/SMLScanner.hh"
	typedef yy::SMLParser::token token;
	typedef yy::SMLParser::token_type token_type;
	#define YY_NO_UNISTD_H
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
	#define TOKEN(t) (yylval->token = t)

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
[0-9]+\.[0-9]*			SAVE_TOKEN; return token::TDOUBLE;
[0-9]+					SAVE_TOKEN; return token::TINTEGER;
\<.+\>\n				SAVE_TOKEN;	return token::TLIST;
[0-9]+[\+\-][0-9]+i 	SAVE_TOKEN; return token::TCOMPLEX;

"="						return TOKEN(token_type::TEQUAL);
":="					return TOKEN(token_type::TASSIGN);
"=="                    return TOKEN(token_type::TCEQ);
"+="					return TOKEN(token_type::TPEQUAL);
"-="					return TOKEN(token_type::TMEQUAL);
"/="					return TOKEN(token_type::TDEQUAL);
"*="					return TOKEN(token_type::TMUEQUAL);
"%="					return TOKEN(token_type::TMOEQUAL);
"!="					return TOKEN(token_type::TNEQUAL);
"<"						return TOKEN(token_type::TCLT);
"<="					return TOKEN(token_type::TCLE);
">"						return TOKEN(token_type::TCGT);
">="					return TOKEN(token_type::TCGE);
"::"					return TOKEN(token_type::TSRO);
"("						return TOKEN(token_type::TLPAREN);
")"						return TOKEN(token_type::TRPAREN);
"{"                     return TOKEN(token_type::TLBRACE);
"}"                     return TOKEN(token_type::TRBRACE);
"."						return TOKEN(token_type::TDOT);
","						return TOKEN(token_type::TCOMMA);
"+"						return TOKEN(token_type::TPLUS);
"-"						return TOKEN(token_type::TMINUS);
"*"						return TOKEN(token_type::TMUL);
"/"						return TOKEN(token_type::TDIV);
"%"						return TOKEN(token_type::TMOD);
"^"						return TOKEN(token_type::TPOW);
"~"                     return TOKEN(token_type::TROOT);
.						std::cout << "Error: Unknown Token" << std::endl; yyterminate();

%%

namespace Mt {
	namespace core {
		namespace lang {
			SMLScanner::SMLScanner(std::istream* in, std::ostream* out) : yyFlexLexer(in, out) { }
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

int yyFlexLexer::yylex(void) {
	std::cerr << "in MtFlexLexer::yylex() !" << std::endl;
    return 0;
}
int yyFlexLexer::yywrap() {
    return 1;
}
