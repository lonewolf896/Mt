/*
	sml.yy - Simple Math Language (SML) bison parser grammar

	TODO (Before I forget)
		Array Access Grammar ([N])
		Proper List and Matrix grammar (Dont rely on the lexer regex)
*/
%skeleton "lalr1.cc"
%require "3.0.4"
%language "C++"

%{
	#include <iostream>
	#include "core/lang/ASTObjs.hh"

	Mt::core::lang::NBlock *rootScope;

	extern int yylex();
	void yyerror(const char* s) { std::cout << "ERROR: " << s << std::endl; }
%}

%union {
	Mt::core::lang::NRoot *node;
	Mt::core::lang::NBlock *block;
	Mt::core::lang::NExpression *expr;
	Mt::core::lang::NStatement *stmt;
	Mt::core::lang::NIdentifier *ident;
	Mt::core::lang::NVariableDeclaration *var_decl;
	std::vector<Mt::core::lang::NVariableDeclaration*> *varvec;
	std::vector<Mt::core::lang::NExpression*> *exprvec;
	Mt::Complex *cmplx;
	bool boolean;
	std::string *string;
	int token;
}

%defines
%define parser_class_name {sml_parser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%define parse.trace
%define parse.error verbose

%token <boolean> TTRUE TFALSE
%token <string> TIDENTIFIER TDOUBLE TINTEGER TLIST TCOMPLEX
%token <token>  TCEQ TEQUAL TASSIGN TNEQUAL TCLT TCLE TCGT TCGE
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT
%token <token> TPLUS TMINUS TMUL TDIV TMOD TPEQUAL TMEQUAL TDEQUAL TMUEQUAL TMOEQUAL TPOW TROOT

%type <ident> ident
%type <expr> numeric expr
%type <varvec> func_decl_args list_decl_args
%type <exprvec> call_args
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl list_decl
%type <token> comparison

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
stmts : stmt { $$ = new Mt::NBlock(); $$->statements.push_back($<stmt>1); }
	  | stmts stmt { $1->statements.push_back($<stmt>2); }
	  ;

/*
	Any statement, variable, function, list, matrix definitions
*/
stmt : var_decl | func_decl | list_decl
	 | expr { $$ = new Mt::core::lang::NExpressionStatement(*$1); }
	 ;

/*
	Blocks/contexts E.G { ... { ... }}
*/
block : TLBRACE stmts TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new Mt::core::lang::NBlock(); }

/*
	Variable Declarations E.G A = B + C
*/
var_decl : ident { $$ = new Mt::core::lang::NVariableDeclaration(*$1); }
		 | ident TASSIGN expr { $$ = Mt::core::lang::NVariableDeclaration(*$1, *$3); }
		 ;

list_decl : ident TASSIGN TCLT list_decl_args TCGT
		   { $$ = new Mt::core::lang::NListDeclaration(*$1, *$3, *$5); delete $5; }
		  ;
/*
	Function definition. I.E f := (...) { ... }
*/
func_decl : ident TASSIGN TLPAREN func_decl_args TRPAREN block
			{ $$ = new Mt::core::lang::NFunctionDeclaration(*$1, *$3, *$5); delete $3; }
		  ;
/*

	List Arguments E.G <> <1,2,...N>
*/
list_decl_args : /* Empty */ { $$ = new Mt::core::lang::VariableList(); }
			   | numeric { $$ = new Mt::core::lang::VariableList(); $$->push_back$($<numeric>1); }
			   | list_decl_args TCOMMA numeric { $1->push_back($<numeric>3); }
			   ;
/*
	Function arguments E.G () (a, b, c, d)
*/
func_decl_args : /* Empty */ { $$ = new Mt::core::lang::VariableList(); }
			   | var_decl { $$ = new Mt::core::lang::VariableList(); $$->push_back($<var_decl>1); }
			   | func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
			   ;

/*
	Valid Identifiers: Must start with a Alpha or _ and can only contain alphanumeric and underscores
*/
ident : TIDENTIFIER { $$ = new Mt::core::lang::NIdentifier(*$1); delete $1; }
	  ;

/*
	Numeric types (Mt::INumeric/Mt::IScalar)
	Integer - Any whole, non-rational number
	Double - Any number with a decimal place
	Complex - Any complex number as represented by X[+-]Yi
*/
numeric : TINTEGER { $$ = new Mt::core::lang::NInteger(atoi($1-c_str())); delete $1; }
		| TDOUBLE { $$ = new Mt::core::lang::NDouble(atof($1->c_str())); delete $1; }
		| TCOMPLEX { $$ = new Mt::core::lang::NComplex(*$1); delete $1; }
		;

/*
	Expressions E.G A = 2+B;
*/
expr : ident TASSIGN expr { $$ = new Mt::core::lang::NAssignment(*$<ident>1, *3); }
	 | ident TLPAREN call_args TRPAREN { $$ = new Mt::core::lang::NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; }
	 | numeric
	 | expr comparison expr { $$ = new Mt::core::langNBinaryOperation(*$1, *$2, *$3); }
	 | TLPAREN expr TRPAREN { $$ = $2; }
	 ;

/*
	function call arguments, I.E () or (1,2,3,...,N)
*/
call_args : /* Empty */ { $$ = new Mt::core::lang::ExpressionList(); }
		  | expr {$$ = new Mt::core::lang::ExpressionList(); $$->push_back($1); }
		  | call_args TCOMMA expr { $1->push_back($3); }
		  ;

/*
	All binary operators ( + - * / ^ > < += -= *= /= >= <=)
*/
comparison : TCEQ | TNEQUAL | TCLT | TCGT | TCLE | TCGE
		   | TPLUS | TMINUS | TMUL | TDIV | TMOD | TPOW
		   | TPEQUAL | TMEQUAL | TDEQUAL | TMUEQUAL | TMOEQUAL
		   | TROOT
		   ;

%%
