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
	#include "core/Types.hh"
%}

%locations
%initial-action
{
	// initialize the initial location object
	@$.begin.filename = @$.end.filename = &driver.streamname;
};

%union {
	Mt::core::lang::NRoot *node;
	Mt::core::lang::NBlock *block;
	Mt::core::lang::NExpression *expr;
	Mt::core::lang::NStatement *stmt;
	Mt::core::lang::NIdentifier *ident;
	Mt::core::lang::NVariableDeclaration *var_decl;
	std::vector<Mt::core::lang::NVariableDeclaration*> *varvec;
	std::vector<Mt::core::lang::NExpression*> *exprvec;
	Mt::core::INumeric *numeric;
	bool boolean;
	std::string *string;
	int token;
}

%defines
%define parser_class_name {SMLParser}
%define parse.assert

%define parse.error verbose

%token END	     0
%token <boolean> TTRUE TFALSE
%token <string> TIDENTIFIER TSCALAR TLIST TCOMPLEX
%token <token>  TCEQ TEQUAL TASSIGN TNEQUAL TCLT TCLE TCGT TCGE
%token <token> TLPAREN TRPAREN TLBRACE TRBRACE TCOMMA TDOT
%token <token> TPLUS TMINUS TMUL TDIV TMOD TPEQUAL TMEQUAL TDEQUAL TMUEQUAL TMOEQUAL TPOW TROOT TSRO

%type <ident> ident
%type <expr> numeric expr
%type <varvec> func_decl_args /* list_decl_args */
%type <exprvec> call_args
%type <block> program stmts block
%type <stmt> stmt var_decl func_decl /*list_decl*/
%type <token> comparison

%left TPLUS TMINUS TSRO
%left TMUL TDIV TMOD

//%name-prefix "Mt::core::lang"
%parse-param { class Mt::core::lang::SMLDriver& driver }

%start program

%{
	#include "core/lang/SMLDriver.hh"
	#include "core/lang/SMLScanner.hh"
	#undef yylex
	#define yylex driver.lexer->lex
%}

%%

/*
	A program as defined by a collection of statements
*/
program : stmts { driver.nblk = $1; }
		;

/*
	Any collection of statements
*/
stmts : stmt { $$ = new Mt::core::lang::NBlock(); $$->statements.push_back($<stmt>1); }
	  | stmts stmt { $1->statements.push_back($<stmt>2); }
	  ;

/*
	Any statement, variable, function, list, matrix definitions
*/
stmt : var_decl | func_decl //| list_decl
	 | expr { $$ = new Mt::core::lang::NExpressionStatement(*$1); }
	 ;

/*
	Blocks/contexts E.G { ... { ... }}
*/
block : TLBRACE stmts TRBRACE { $$ = $2; }
	  | TLBRACE TRBRACE { $$ = new Mt::core::lang::NBlock(); }

/*
	Numeric types (Mt::INumeric/Mt::IScalar)
	Scalar - Any numeric that is not complex
	Complex - Any complex number as represented by X[+-]Yi
*/
numeric : TSCALAR { $$ = new Mt::core::lang::NScalar((mtfloat_t)atof($1->c_str())); delete $1; }
		| TMINUS TSCALAR { $$ = new Mt::core::lang::NScalar(-(mtfloat_t)atof($2->c_str())); delete $2; }
		| TCOMPLEX { $$ = new Mt::core::lang::NComplex(*$1); delete $1; }
		| TMINUS TCOMPLEX { $$ = new Mt::core::lang::NComplex(*$2); delete $2; }
		;

/*
	Variable Declarations E.G A := B + C
*/
var_decl : ident { $$ = new Mt::core::lang::NVariableDeclaration(*$1); }
		 | ident TASSIGN expr { $$ = new Mt::core::lang::NVariableDeclaration(*$1, $3); }
		 ;

//list_decl : ident TASSIGN TCLT list_decl_args TCGT
//		   { $$ = new Mt::core::lang::NListDeclaration(*$1, *$4, *$6); delete $4; }
//		  ;

/*
	Function definition. I.E f := (...) { ... }
*/
func_decl : ident TASSIGN TLPAREN func_decl_args TRPAREN block
			{ $$ = new Mt::core::lang::NFunctionDeclaration(*$1, *$4, *$6); delete $4; }
		  ;
/*

	List Arguments E.G <> <1,2,...N>
*/

//list_decl_args : /* Empty */ { $$ = new Mt::core::lang::VariableList(); }
//			   | numeric { $$ = new Mt::core::lang::VariableList(); $$->push_back($<numeric>1); }
//			   | list_decl_args TCOMMA numeric { $1->push_back($<numeric>3); }
//			   ;

/*
	Function arguments E.G () (a, b, c, d)
*/
func_decl_args : /* Empty */ { $$ = new Mt::core::lang::VariableList(); }
			   | var_decl { $$ = new Mt::core::lang::VariableList(); $$->push_back($<var_decl>1); }
			   | func_decl_args TCOMMA var_decl { $1->push_back($<var_decl>3); }
			   ;

/*
	Scope Resolution E.G Mt::func(...) Mt::sub::func()
*/
//scope : ident TSRO  ident TLPAREN call_args TRPAREN { $$ = }
//	  | ident TSRO scope
//	  ;

/*
	Valid Identifiers: Must start with a Alpha or _ and can only contain alphanumeric and underscores
*/
ident : TIDENTIFIER { $$ = new Mt::core::lang::NIdentifier(*$1); delete $1; }
	  ;


/*
	Expressions E.G A := 2+B;
*/
expr : ident TASSIGN expr { $$ = new Mt::core::lang::NAssignment(*$<ident>1, *$3); }
	 | ident TLPAREN call_args TRPAREN { $$ = new Mt::core::lang::NMethodCall(*$1, *$3); delete $3; }
	 | ident { $<ident>$ = $1; }
	 | numeric
	 | expr comparison expr { $$ = new Mt::core::lang::NBinaryOperator(*$1, $2, *$3); }
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
	All binary operators ( + - * / ^ > < += -= *= /= >= <= ~)
*/
comparison : TCEQ | TNEQUAL | TCLT | TCGT | TCLE | TCGE
		   | TPLUS | TMINUS | TMUL | TDIV | TMOD | TPOW
		   | TPEQUAL | TMEQUAL | TDEQUAL | TMUEQUAL | TMOEQUAL
		   | TROOT
		   ;

%%

void yy::SMLParser::error(const SMLParser::location_type& l, const std::string& m) {
	driver.Error(l, m);
}
