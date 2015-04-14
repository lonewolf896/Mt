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
				void Evaluate(Mt::core::lang::NBlock* blk, std::map<std::string, Mt::core::IMtObject>& GST, std::string rawInput);
			};
		}
	}
}
