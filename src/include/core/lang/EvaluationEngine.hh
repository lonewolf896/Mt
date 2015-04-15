/*
	EvaluationEngine.hh - AST Evaluation Engine
*/
#pragma once

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
	
#include "core/IMtObject.hh"
#include "ASTObjs.hh"
#include "Parser.hh"

namespace Mt {
	namespace core {
		namespace lang {
			/*! \class EvaluationEngine
				\brief Mechanics for Resolving and evaluating the AST
			*/
			class EvaluationEngine {
			private:
				bool debug_evaluation;
				std::string GetNameFromMagik(MAGIK m);
				std::string GetTokenName(yy::SMLParser::token_type t);
				Mt::core::IMtObject* ProcessExpression(NExpression* expr, std::map<std::string, Mt::core::IMtObject>& GST);
				Mt::core::IMtObject* DoBinaryOperation(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs, yy::SMLParser::token_type oper, std::map<std::string, Mt::core::IMtObject>& GST);
				
				Mt::core::IMtObject* BinaryAdd(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs);
				Mt::core::IMtObject* BinaryMinus(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs);		
				Mt::core::IMtObject* BinaryMultiply(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs);
				Mt::core::IMtObject* BinaryDivied(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs);

				void PrintResult(Mt::core::IMtObject* res, std::string input);
			public:
				/*!
					Create a new instance of the Evaluation Engine with defaults
				*/
				EvaluationEngine(void);
				~EvaluationEngine(void);
				/*!
					Toggles the debug trace flag
				*/
				void ToggleDebug(void);
				/*!
					Evaluates the given AST and places the results in the GST
					\param[in] blk A pointer to the current AST block
					\param[in] GST A reference to the global symbol table
					\param[in] rawInput the raw unparsed expression
				*/
				void Evaluate(Mt::core::lang::NBlock* blk, std::map<std::string, Mt::core::IMtObject>& GST, std::string rawInput = "<<NONE>>");
			};
		}
	}
}
