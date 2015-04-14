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
					case _NSCALAR:
						return "NScalar";
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

			std::string EvaluationEngine::GetTokenName(yy::SMLParser::token_type t) {
				switch(t) {
					case yy::SMLParser::token_type::TPLUS:
						return "TPLUS";
					case yy::SMLParser::token_type::TMINUS:
						return "TMINUS";
					case yy::SMLParser::token_type::TMUL:
						return "TMUL";
					case yy::SMLParser::token_type::TDIV:
						return "TDIV";
					case yy::SMLParser::token_type::TMOD:
						return "TMOD";
					case yy::SMLParser::token_type::TPOW:
						return "TPOW";
					case yy::SMLParser::token_type::TROOT:
						return "TROOT";
					case yy::SMLParser::token_type::TCGT:
						return "TCGT";
					case yy::SMLParser::token_type::TCLT:
						return "TCLT";
					case yy::SMLParser::token_type::TCGE:
						return "TCGE";
					case yy::SMLParser::token_type::TCLE:
						return "TCLE";
					case yy::SMLParser::token_type::TMOEQUAL:
						return "TMOEQUAL";
					case yy::SMLParser::token_type::TMUEQUAL:
						return "TMUEQUAL";
					case yy::SMLParser::token_type::TDEQUAL:
						return "TDEQUAL";
					case yy::SMLParser::token_type::TMEQUAL:
						return "TMEQUAL";
					case yy::SMLParser::token_type::TPEQUAL:
						return "TPEQUAL";
					case yy::SMLParser::token_type::TASSIGN:
						return "TASSIGN";
					case yy::SMLParser::token_type::TEQUAL:
						return "TEQUAL";
					case yy::SMLParser::token_type::TCEQ:
						return "TCEQ";
					case yy::SMLParser::token_type::TSRO:
						return "TSRO";
					default:
						return "<<UNKNOWN>>";
				}
			}

			void EvaluationEngine::ProcessExpressionStmnt(NExpressionStatement* expr, std::map<std::string, Mt::core::IMtObject>& GST) {
				if(this->debug_evaluation)
								std::cout << "Expression " << expr << " is of type " << this->GetNameFromMagik(expr->_expression.type) << std::endl;
				this->ProcessExpression(&(expr->_expression), GST);
			}

			void EvaluationEngine::ProcessExpression(NExpression* expr, std::map<std::string, Mt::core::IMtObject>& GST) {
				switch(expr->type) {
					case _NBLOCK: {
						auto blk = dynamic_cast<NBlock*>(expr);
						this->Evaluate(blk, GST);
						break;
					} case _NBINARYOPERATOR: {
						auto nbin = dynamic_cast<NBinaryOperator*>(expr);
						if(this->debug_evaluation)
							std::cout << "Binary Operation at " << nbin << " has operator of " << this->GetTokenName(static_cast<yy::SMLParser::token_type>(nbin->_op)) << std::endl;
						this->ProcessExpression(&(nbin->_lhs), GST);
						this->ProcessExpression(&(nbin->_rhs), GST);
						break;
					} case _NMETHODCALL: {

					} case _NIDENTIFIER: {

						break;
					} case _NCOMPLEX: {

						break;
					} case _NSCALAR: {
					  	// Capture both of these, because they are both backed by Scalar
					  	if(this->debug_evaluation)
					  		std::cout << "Expression at " << expr << " is a NScalar with value " << dynamic_cast<NScalar*>(expr)->_s << std::endl;
					  	break;
					  }
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
							
							break;
						} case _NEXPRESSIONSTATEMENT: {
							auto expr = dynamic_cast<NExpressionStatement*>(statement);
							this->ProcessExpressionStmnt(expr, GST);
							break;
						} case _NFUNCTIONDECLARATION: {
							
							break;
						} case _NLISTDECLARATION: {
							
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
