/*
	EvaluationEngine.cc - AST Evaluation Engine
*/
#include "core/lang/EvaluationEngine.hh"


namespace Mt {
	namespace core {
		namespace lang {
			EvaluationEngine::EvaluationEngine(void) : debug_evaluation(false) {

			}

			EvaluationEngine::~EvaluationEngine(void) {

			}

			void EvaluationEngine::ToggleDebug(void) {
				this->debug_evaluation = !this->debug_evaluation;
			}

			std::string EvaluationEngine::GetNameFromMagik(MAGIK m) {
				switch(m) {
					case _NROOT:
						return "NRoot";
					case _NSTATEMENT:
						return "NStatement";
					case _NEXPRESSION:
						return "NExpression";
					case _NINTEGER:
						return "NInteger";
					case _NDOUBLE:
						return "NDouble";
					case _NCOMPLEX:
						return "NComplex";
					case _NIDENTIFIER:
						return "NIdentifier";
					case _NVARIABLEDECLARATION:
						return "NVariableDeclaration";
					case _NMETHODCALL:
						return "NMethodCall";
					case _NBINARYOPERATOR:
						return "NBinaryOperator";
					case _NASSIGNMENT:
						return "NAssignment";
					case _NBLOCK:
						return "NBlock";
					case _NEXPRESSIONSTATEMENT:
						return "NExpressionStatement";
					case _NFUNCTIONDECLARATION:
						return "NFunctionDeclaration";
					case _NLISTDECLARATION:
						return "NListDeclaration";
					default:
						return "<<UNKNOWN>>";
				}
			}

			void EvaluationEngine::Evaluate(Mt::core::lang::NBlock* blk, std::map<std::string, Mt::core::IMtObject>& GST, std::string rawInput) {
				if(this->debug_evaluation) {
					std::cout << "Evaluating input" << std::endl << "Performing AST sanity check" << std::endl;
				}
				// Add a trap in case the AST is passed as a null or empty pointer.
				if(blk == nullptr) {
					std::cerr << "Error: AST Null, Parser on fire?" << std::endl;
					return;
				}
				if(this->debug_evaluation) {
					std::cout << "AST at " << blk << std::endl;
					std::cout << "Current expression has " << blk->statements.size() << " statement(s)" << std::endl;
					std::cout << "The Global Symbol Table has " << GST.size() << " symbol(s)" << std::endl;
					std::cout << "Iterating over statements" << std::endl;
				}
				for(auto statement : blk->statements) {
					if(this->debug_evaluation) {
						std::cout << "Evaluating statement at " << statement << " of type " << this->GetNameFromMagik(statement->type) << std::endl;
					}
					switch(statement->type) {
						case _NVARIABLEDECLARATION: {
							std::cout << "VARDECL" << std::endl;
							break;
						} case _NEXPRESSIONSTATEMENT: {
							std::cout << "EXPRSS" << std::endl;
							break;
						} case _NFUNCTIONDECLARATION: {
							std::cout << "FUNCDEL" << std::endl;
							break;
						} case _NLISTDECLARATION: {
							std::cout << "LISTDECL" << std::endl;
							break;
						} default:
							std::cerr << "Unknown statement type: " << this->GetNameFromMagik(statement->type) << std::endl;
					}
				}
		#pragma message("TODO: Properly evaluate AST")
				std::cout << " " << rawInput << std::endl;
			}
		}
	}
}
