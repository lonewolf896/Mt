/*
	ASTObjs.hh - Objects that are represented in the Abstract syntax tree
*/
#pragma once

#include "core/INumeric.hh"

#include "objects/Scalar.hh"
#include "objects/Complex.hh"

#include <vector>
#include <map>
#include <string>


namespace Mt {
	namespace core {
		namespace lang {
			/*! \class NRoot
				\brief Lexical Expression Base

				This is an empty class that serves as the base for all SML lexical objects

			*/
			class NRoot {

			};
			/*! \class NStatment 
				\brief SML Lexical Statement

				This is an empty class the serves as the base for all SML lexical statements
			*/
			class NStatement : NRoot {

			};
			/*! \class NExpression
				\brief SML Lexical Expression

				This is an empty class that serves as the base for all SML expressions
			*/
			class NExpression : NRoot {

			};
			/*! \class NInteger
				\brief SML Integer Representation

				This is a lexical object that represents the Mt::objects::Integer type
			*/
			class NInteger : NExpression {
				public:
					Mt::objects::Scalar i;
					NInteger(int val) : i(val) {}
			};
			/*! \class NDouble
				\brief SML Double Representation

				This is a lexical object that represents the Mt::objects::Double type
			*/
			class NDouble : NExpression{
				public:
					Mt::objects::Scalar d;
					NDouble(double val) : d(val) {}
			};
			/*! \class NComplex
				\brief SML Complex Representation

				This is a lexical object that represents the Mt::objects::Complex type
			*/
			class NComplex : NExpression {
				public:
					Mt::objects::Complex c;
					NComplex(const std::string cplx) {}
					NComplex(const char* cpkx) {}
			};
			/*! \class NIdentifier
				\brief SML Lexical Identifier

				This class holds a SML identifier, this can be a function or variable name.

				An SML identifier can be any alphanumeric string with any amount of underscores contained 
				within as long as it starts only with an alpha that matches [a-zA-Z]
			*/
			class NIdentifier : NExpression {
				public:
					std::string name;
					NIdentifier(const std::string& name) : name(name) { }
			};
			/*! \class NVariableDeclaration
				\brief SML Variable Declaration Representation

				This class represents a SML variable declaration in the form of:

				~~~
				NIdentifer := NExpression
				~~~
			*/
			class NVariableDeclaration : public NStatement {
				public:
					NIdentifier& id;
					NExpression *assignmentExpr;
					NVariableDeclaration(NIdentifier& id) :
						id(id) { }
					NVariableDeclaration(NIdentifier& id, NExpression *assignmentExpr) :
						id(id), assignmentExpr(assignmentExpr) { }
			};


			typedef std::vector<Mt::core::lang::NStatement*> StatementList;
			typedef std::vector<Mt::core::lang::NExpression*> ExpressionList;
			typedef std::vector<Mt::core::lang::NVariableDeclaration*> VariableList;

			/*! \class NMethodCall
				\brief SML Method Call Representation

				This class stores an SML method call in the form of:

				~~~
				NIdentifier := ExpressionList
				~~~

				where `ExpressionList` is `std::vector<Mt::core::lang::NExpression*>`
			*/
			class NMethodCall : NExpression {
				public:
					const NIdentifier& id;
					ExpressionList arguments;
					NMethodCall(const NIdentifier& id, ExpressionList& arguments) : id(id), arguments(arguments) { }
					NMethodCall(const NIdentifier& id) : id(id) { }
			};
			/*! \class NBinaryOperator
				\brief SML Binary Operator Representation

				This class is a sub-class of Mt::core::lang::NExpression that holds any binary operation in the form of:

				~~~
				NExpression OPERATOR NExpression
				~~~
			*/
			class NBinaryOperator : public NExpression {
				public:
					int op;
					NExpression& lhs;
					NExpression& rhs;
					NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
						lhs(lhs), rhs(rhs), op(op) { }
			};
			/*! \class NAssigmnet 
				\brief SML Assignment Operation Representation
			
				This class is a sub-class of Mt::core::lang::NExpression that holds any SML assignment
				operation in the from of:

				~~~
				NIdentifer := NExpression
				~~~
			*/
			class NAssignment : public NExpression {
				public:
					NIdentifier& lhs;
					NExpression& rhs;
					NAssignment(NIdentifier& lhs, NExpression& rhs) :
						lhs(lhs), rhs(rhs) { }
			};
			/*! \class NBlock
				\brief SML Scope Representation

				This class is a container for a collection of SML statements
			*/
			class NBlock : public NExpression {
				public:
					StatementList statements;
					NBlock() { }
			};
			/*! \class NExpressionStatement
				\brief SML Expression Statement Representation

				This class is a sub-class of Mt::core::lang::NStatement where it allows for a NExpression
				as a statement.
			*/
			class NExpressionStatement : public NStatement {
				public:
					NExpression& expression;
					NExpressionStatement(NExpression& expression) :
						expression(expression) { }
			};
			/*! \class NFunctionDeclaration
				\brief SML Function Declaration Representation

				This class represents the definition of an SML function in the form of:

				~~~
				NIdentifer := VariableList
				~~~

				where `VariableList` is `std::vector<Mt::core::lang::NVariableDeclaration*>`
			*/
			class NFunctionDeclaration : public NStatement {
				public:
					const NIdentifier& id;
					VariableList arguments;
					NBlock& block;
					NFunctionDeclaration(const NIdentifier& id,
							const VariableList& arguments, NBlock& block) :
						id(id), arguments(arguments), block(block) { }
			};

			class NListDeclaration : public NStatement {
				public:
					const NIdentifier& id;
					VariableList arguments;
					NBlock& block;
					NListDeclaration(const NIdentifier& id,
							const VariableList& arguments, NBlock& block) :
						id(id), arguments(arguments), block(block) { }
			};
		}
	}
}
