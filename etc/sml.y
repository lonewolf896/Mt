/*
	sml.y - Simple Math Language (SML) bison parser grammar

	TODO (Before I forget)
		Array Access Grammar ([N])
		Proper List and Matrix grammar (Dont rely on the lexer regex)
*/
%{
	#include <iostream>
	#include "core/lang/node.hpp"
	#include "objects/Complex.hpp"

	NScope *rootScope;

	extern int yylex();
	void yyerror(const char* s) { std::cout << "ERROR: " << s << std::endl; }
%}

%union {

	Mt::Complex *cmplx;
	bool boolean;
	std::string *string;
	int token;
}

%token <boolean> TTRUE TFALSE
%token <string> TIDENTIFIER TDOUBLE TINTEGER TLIST TCOMPLEX
%token <token>  TCEQ TEQUAL TASSIGN TNEQUAL TCLT TCLE TCGT TCGE
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT
%token <token> TPLUS TMINUS TMUL TDIV TMOD TPEQUAL TMEQUAL TDEQUAL TMUEQUAL TMOEQUAL TPOW



%left TPLUS TMINUS
%left TMUL TDIV TMOD

%start program

%%

/*
	A program as defined by a collection of statements
*/
program : stmts { rootScope = $1; }
		;

/*
	Any collection of statements
*/
stmts : stmt { $$ = new NScope(); $$->statments.puch_back($<stmt>1); }
	  | stmts stmt { $1->statments.push_back($<stmt>2); }
	  ;

/*
	Any statement, variable, function, list, matrix definitions
*/
stmt : var_decl | func_decl | list_decl
	 | expr { $$ = new NExpressionStatement(*$1); }
	 ;

/*
	Blocks/contexts E.G { ... { ... }}
*/
block : TLBRACE stmts TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new NBlock(); }

/*
	Variable Declarations E.G A = B + C
*/
var_decl : ident { $$ = new NVariableDeclaration(*$1, *$2); }
		 | ident TASSIGN expr { $$ = NVariableDeclaration(*$1, *$2, *$4); }
		 ;

list_decl : ident TASSIGN TCLT list_decl_args TCGT
		   { $$ = new NListDeclaration(*$1, *$2, *$4, *$6); delete $4; }
		  ;
/*
	Function definition. I.E f := (...) { ... }
*/
func_decl : ident TASSIGN TLPAREN func_decl_args TRPAREN block
		 	{ $$ = new NFunctionDeclaration(*$1, *$2, *$4, *$6); delete $4; }
		  ;
/*

	List Arguments E.G <> <1,2,...N>
*/
list_decl_args : /* Empty */ { $$ = new VariableList(); }
			   | numeric { $$ = new VariableList(); $$->push_back$($<numeric>1); }
			   | list_decl_args TCOMMA numeric { $1->push_back($<numeric>3); }
			   ;
/*
	Function arguments E.G () (a, b, c, d)
*/
func_decl_args : /* Empty */ { $$ = new VariableList(); }
			   | var_decl { $$ = new VariableList(); $$->push_back($<var_decl>1); }
			   | func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
			   ;

/*
	Valid Identifiers: Must start with a Alpha or _ and can only contain alphanumeric and underscores
*/
ident : TIDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
	  ;

/*
	Numeric types (Mt::INumeric)
	Integer - Any whole, non-rational number
	Double - Any number with a decimal place
	Complex - Any complex number as represented by X[+-]Yi
*/
numeric : TINTEGER { $$ = new Mt::Integer(atoi($1-c_str())); delete $1; }
		| TDOUBLE { $$ = new Mt::Double(atof($1->c_str())); delete $1; }
		| TCOMPLEX { $$ = new Mt::Complex(*$1); delete $1; }
		;

/*
	Expressions E.G A = 2+B;
*/
expr : ident TASSIGN expr { $$ = new NAssignment(*$<ident>1, *3); }
	 | ident TLPAREN call_args TRPAREN { $$ = new NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; }
	 | numeric
	 | expr comparison expr { $$ = new NBinaryOperation(*$1, *$2, *$3); }
	 | TLPAREN expr TRPAREN { $$ = $2; }
	 ;

/*
	function call arguments, I.E () or (1,2,3,...,N)
*/
call_args : /* Empty */ { $$ = new ExpressionList(); }
	 	  | expr {$$ = new ExpressionList(); $$->push_back($1); }
	 	  | call_args TCOMMA expr { $1->push_back($3); }
	 	  ;

/*
	All binary operators ( + - * / ^ > < += -= *= /= >= <=)
*/
comparison : TCEQ | TNEQUAL | TCLT | TCGT | TCLE | TCGE
		   | TPLUS | TMINUS | TMUL | TDIV | TMOD | TPOW
		   | TPEQUAL | TMEQUAL | TDEQUAL | TMUEQUAL | TMOEQUAL
		   ;

%%
