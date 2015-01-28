// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 9 "etc/sml.yy" // lalr1.cc:404

	#include <iostream>
	#include "core/lang/ASTObjs.hh"

	Mt::NBlock *rootScope;

	extern int yylex();
	void yyerror(const char* s) { std::cout << "ERROR: " << s << std::endl; }

#line 46 "src/Parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "core/lang/Parser.hh"

// User implementation prologue.

#line 60 "src/Parser.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif



// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 127 "src/Parser.cc" // lalr1.cc:479

  /// Build a parser object.
  parser::parser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
  {}

  parser::~parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  parser::syntax_error::syntax_error (const std::string& m)
    : std::runtime_error (m)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
  {
    value = other.value;
  }


  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v)
    : Base (t)
    , value (v)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  inline
  parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
  }

  // by_type.
  inline
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  parser::symbol_number_type
  parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }


  template <typename Base>
  inline
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.type_get ());
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " (";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 60 "etc/sml.yy" // lalr1.cc:859
    { rootScope = (yystack_[0].value.block); }
#line 552 "src/Parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 66 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.block) = new Mt::NBlock(); (yylhs.value.block)->statements.push_back((yystack_[0].value.stmt)); }
#line 558 "src/Parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 67 "etc/sml.yy" // lalr1.cc:859
    { (yystack_[1].value.block)->statements.push_back((yystack_[0].value.stmt)); }
#line 564 "src/Parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 74 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.stmt) = new Mt::NExpressionStatement(*(yystack_[0].value.expr)); }
#line 570 "src/Parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 80 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.block) = (yystack_[1].value.block); }
#line 576 "src/Parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 81 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.block) = new Mt::NBlock(); }
#line 582 "src/Parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 86 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.stmt) = new Mt::NVariableDeclaration(*(yystack_[0].value.ident)); }
#line 588 "src/Parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 87 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.stmt) = Mt::NVariableDeclaration(*(yystack_[2].value.ident), *(yystack_[0].value.expr)); }
#line 594 "src/Parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 91 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.stmt) = new Mt::NListDeclaration(*(yystack_[4].value.ident), *(yystack_[2].value.token), *(yystack_[0].value.token)); delete (yystack_[0].value.token); }
#line 600 "src/Parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 97 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.stmt) = new NFunctionDeclaration(*(yystack_[5].value.ident), *(yystack_[3].value.token), *(yystack_[1].value.token)); delete (yystack_[3].value.token); }
#line 606 "src/Parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 103 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.varvec) = new VariableList(); }
#line 612 "src/Parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 104 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.varvec) = new VariableList(); (yylhs.value.varvec)->push_back$((yystack_[0].value.numeric)); }
#line 618 "src/Parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 105 "etc/sml.yy" // lalr1.cc:859
    { (yystack_[2].value.varvec)->push_back((yystack_[0].value.numeric)); }
#line 624 "src/Parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 110 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.varvec) = new Mt::VariableList(); }
#line 630 "src/Parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 111 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.varvec) = new Mt::VariableList(); (yylhs.value.varvec)->push_back((yystack_[0].value.var_decl)); }
#line 636 "src/Parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 112 "etc/sml.yy" // lalr1.cc:859
    { (yystack_[2].value.varvec)->push_back((yystack_[0].value.var_decl)); }
#line 642 "src/Parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 118 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.ident) = new Mt::NIdentifier(*(yystack_[0].value.string)); delete (yystack_[0].value.string); }
#line 648 "src/Parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 127 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = new Mt::NInteger(atoi((yystack_[0].value.string)-c_str())); delete (yystack_[0].value.string); }
#line 654 "src/Parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 128 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = new Mt::NDouble(atof((yystack_[0].value.string)->c_str())); delete (yystack_[0].value.string); }
#line 660 "src/Parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 129 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = new Mt::NComplex(*(yystack_[0].value.string)); delete (yystack_[0].value.string); }
#line 666 "src/Parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 135 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = new Mt::NAssignment(*(yystack_[2].value.ident), *3); }
#line 672 "src/Parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 136 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = new Mt::NMethodCall(*(yystack_[3].value.ident), *(yystack_[1].value.exprvec)); delete (yystack_[1].value.exprvec); }
#line 678 "src/Parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 137 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.ident) = (yystack_[0].value.ident); }
#line 684 "src/Parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 139 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = new Mt::NBinaryOperation(*(yystack_[2].value.expr), *(yystack_[1].value.token), *(yystack_[0].value.expr)); }
#line 690 "src/Parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 140 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.expr) = (yystack_[1].value.expr); }
#line 696 "src/Parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 146 "etc/sml.yy" // lalr1.cc:859
    { (yylhs.value.exprvec) = new Mt::ExpressionList(); }
#line 702 "src/Parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 147 "etc/sml.yy" // lalr1.cc:859
    {(yylhs.value.exprvec) = new Mt::ExpressionList(); (yylhs.value.exprvec)->push_back((yystack_[0].value.expr)); }
#line 708 "src/Parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 148 "etc/sml.yy" // lalr1.cc:859
    { (yystack_[2].value.exprvec)->push_back((yystack_[0].value.expr)); }
#line 714 "src/Parser.cc" // lalr1.cc:859
    break;


#line 718 "src/Parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yysyntax_error_ (yystack_[0].state, yyla));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }


      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char parser::yypact_ninf_ = -39;

  const signed char parser::yytable_ninf_ = -12;

  const signed char
  parser::yypact_[] =
  {
     111,   -39,   -39,   -39,   -39,   111,     2,   111,   -39,   -39,
     -39,   -39,    12,   -39,    81,    14,    56,   -39,   -39,    39,
     111,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -39,   111,   111,
     -39,    30,   111,    81,    81,   -16,    81,    81,    25,   -39,
     -39,    32,   109,   -39,   111,   -39,    30,    -6,    44,   111,
      81,   -39,     4,   -39,   -39,    40,   -39,    22,   111,   -39,
      81
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,    21,    23,    22,    24,     0,     0,     2,     3,     5,
       7,     6,    27,    28,     8,    27,     0,     1,     4,     0,
      31,    34,    35,    36,    38,    37,    39,    40,    41,    42,
      43,    44,    46,    47,    48,    49,    50,    45,     0,     0,
      30,    15,    18,    12,    32,     0,    29,    25,     0,    16,
      19,     0,    27,    26,     0,    13,     0,     0,     0,     0,
      33,    17,     0,    14,    20,    11,    10,     0,     0,     9,
      12
  };

  const signed char
  parser::yypgoto_[] =
  {
     -39,   -39,    -3,    -2,   -39,   -38,   -39,   -39,   -39,   -39,
       0,   -33,    -4,   -39,   -39
  };

  const signed char
  parser::yydefgoto_[] =
  {
      -1,     6,     7,     8,    63,     9,    10,    11,    48,    51,
      15,    13,    14,    45,    38
  };

  const signed char
  parser::yytable_[] =
  {
      12,    16,    17,    53,    50,    18,    54,    12,    49,     1,
       2,     3,   -11,     4,    62,    43,    44,   -11,   -11,   -11,
      64,   -11,     5,    61,    19,    66,    39,     1,     2,     3,
      20,     4,    20,   -11,    46,    47,     2,     3,    16,     4,
       5,    55,    52,    69,     1,     2,     3,    56,     4,     1,
      60,    57,    68,    41,    58,    43,     0,    42,    65,    67,
       0,     0,    12,     0,    70,    18,    21,    12,     0,    22,
      23,    24,    25,    26,     0,    40,     0,     0,     0,     0,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    21,     0,     0,    22,    23,    24,    25,    26,     0,
       0,     0,     0,     0,     0,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,     1,     2,     3,     0,
       4,    59,     0,     0,     0,     0,     0,    20,   -11,     5,
       0,   -11
  };

  const signed char
  parser::yycheck_[] =
  {
       0,     5,     0,    19,    42,     7,    22,     7,    41,     5,
       6,     7,     0,     9,    20,    19,    20,     5,     6,     7,
      58,     9,    18,    56,    12,    21,    12,     5,     6,     7,
      18,     9,    18,    21,    38,    39,     6,     7,    42,     9,
      18,    16,    42,    21,     5,     6,     7,    22,     9,     5,
      54,    19,    12,    14,    22,    59,    -1,    18,    58,    62,
      -1,    -1,    62,    -1,    68,    67,    10,    67,    -1,    13,
      14,    15,    16,    17,    -1,    19,    -1,    -1,    -1,    -1,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    10,    -1,    -1,    13,    14,    15,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,     5,     6,     7,    -1,
       9,    12,    -1,    -1,    -1,    -1,    -1,    18,    19,    18,
      -1,    22
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,     5,     6,     7,     9,    18,    36,    37,    38,    40,
      41,    42,    45,    46,    47,    45,    47,     0,    38,    12,
      18,    10,    13,    14,    15,    16,    17,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    49,    12,
      19,    14,    18,    47,    47,    48,    47,    47,    43,    46,
      40,    44,    45,    19,    22,    16,    22,    19,    22,    12,
      47,    46,    20,    39,    40,    45,    21,    37,    12,    21,
      47
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    35,    36,    37,    37,    38,    38,    38,    38,    39,
      39,    40,    40,    41,    42,    43,    43,    43,    44,    44,
      44,    45,    46,    46,    46,    47,    47,    47,    47,    47,
      47,    48,    48,    48,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49
  };

  const unsigned char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     2,     1,     1,     1,     1,     3,
       2,     1,     3,     5,     6,     0,     1,     3,     0,     1,
       3,     1,     1,     1,     1,     3,     4,     1,     1,     3,
       3,     0,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "TTRUE", "TFALSE", "TIDENTIFIER",
  "TDOUBLE", "TINTEGER", "TLIST", "TCOMPLEX", "TCEQ", "TEQUAL", "TASSIGN",
  "TNEQUAL", "TCLT", "TCLE", "TCGT", "TCGE", "TLPAREN", "TRPAREN",
  "TLBRACE", "TRBRACE", "TCOMMA", "TDOT", "TPLUS", "TMINUS", "TMUL",
  "TDIV", "TMOD", "TPEQUAL", "TMEQUAL", "TDEQUAL", "TMUEQUAL", "TMOEQUAL",
  "TPOW", "$accept", "program", "stmts", "stmt", "block", "var_decl",
  "list_decl", "func_decl", "list_decl_args", "func_decl_args", "ident",
  "numeric", "expr", "call_args", "comparison", YY_NULLPTR
  };


  const unsigned char
  parser::yyrline_[] =
  {
       0,    60,    60,    66,    67,    73,    73,    73,    74,    80,
      81,    86,    87,    90,    96,   103,   104,   105,   110,   111,
     112,   118,   127,   128,   129,   135,   136,   137,   138,   139,
     140,   146,   147,   148,   154,   154,   154,   154,   154,   154,
     155,   155,   155,   155,   155,   155,   156,   156,   156,   156,
     156
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
    };
    const unsigned int user_token_number_max_ = 289;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1106 "src/Parser.cc" // lalr1.cc:1167
#line 159 "etc/sml.yy" // lalr1.cc:1168

