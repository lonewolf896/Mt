/*
	ASTObjs.hh - Objects that are represented in the Abstract syntax tree
*/
#pragma once

#include "core/INumeric.hh"
#include "core/IScalar.hh"

#include "objects/Complex.hh"
#include "objects/Integer.hh"
#include "objects/Double.hh"

#include <vector>
#include <map>
#include <string>


namespace Mt {

	class NRoot {

	};

	class NStatement : NRoot {

	};

	class NExpression : NRoot {

	};

	class NInteger : NExpression {
		public:
			Integer i;
			NInteger(int val) : i(val) {}
	};

	class NDouble : NExpression{
		public:
			Double d;
			NDouble(int val) : d(val) {}
	};

	class NComplex : NExpression {
		public:
			Complex c;
			NComplex(const std::string cplx) {}
			NComplex(const char* cpkx) {}
	};

	class NIdentifier : NExpression {
		public:
			std::string name;
			NIdentifier(const std::string& name) : name(name) { }
	};

	class NVariableDeclaration : public NStatement {
		public:
		    NIdentifier& id;
		    NExpression *assignmentExpr;
		    NVariableDeclaration(NIdentifier& id) :
		        id(id) { }
		    NVariableDeclaration(NIdentifier& id, NExpression *assignmentExpr) :
		        id(id), assignmentExpr(assignmentExpr) { }
	};


	typedef std::vector<Mt::NStatement*> StatementList;
	typedef std::vector<Mt::NExpression*> ExpressionList;
	typedef std::vector<Mt::NVariableDeclaration*> VariableList;

	class NMethodCall : NExpression {
		public:
			const NIdentifier& id;
		    ExpressionList arguments;
		    NMethodCall(const NIdentifier& id, ExpressionList& arguments) : id(id), arguments(arguments) { }
		    NMethodCall(const NIdentifier& id) : id(id) { }
	};

	class NBinaryOperator : public NExpression {
		public:
		    int op;
		    NExpression& lhs;
		    NExpression& rhs;
		    NBinaryOperator(NExpression& lhs, int op, NExpression& rhs) :
		        lhs(lhs), rhs(rhs), op(op) { }
	};

	class NAssignment : public NExpression {
		public:
		    NIdentifier& lhs;
		    NExpression& rhs;
		    NAssignment(NIdentifier& lhs, NExpression& rhs) :
		        lhs(lhs), rhs(rhs) { }
	};

	class NBlock : public NExpression {
		public:
		    StatementList statements;
		    NBlock() { }
	};

	class NExpressionStatement : public NStatement {
		public:
		    NExpression& expression;
		    NExpressionStatement(NExpression& expression) :
		        expression(expression) { }
	};

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
