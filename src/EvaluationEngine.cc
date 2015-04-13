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
						std::cout << "Evaluating statement at " << statement << " of type " << typeid(statement).name() << std::endl;
					}
				}
		#pragma message("TODO: Properly evaluate AST")
				std::cout << " " << rawInput << std::endl;
			}
		}
	}
}
