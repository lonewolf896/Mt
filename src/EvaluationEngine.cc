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

			Mt::core::IMtObject* EvaluationEngine::ProcessExpression(NExpression* expr, std::map<std::string, Mt::core::IMtObject>& GST) {
				switch(expr->type) {
					case _NBLOCK: {
						auto blk = dynamic_cast<NBlock*>(expr);
						this->Evaluate(blk, GST);
						break;
					} case _NBINARYOPERATOR: {
						auto nbin = dynamic_cast<NBinaryOperator*>(expr);
						if(this->debug_evaluation)
							std::cout << "Binary Operation at " << nbin << " has operator of " << this->GetTokenName(static_cast<yy::SMLParser::token_type>(nbin->_op)) << std::endl;
						auto lhs = this->ProcessExpression(&(nbin->_lhs), GST);
						auto rhs = this->ProcessExpression(&(nbin->_rhs), GST);
						return this->DoBinaryOperation(rhs, lhs, static_cast<yy::SMLParser::token_type>(nbin->_op), GST);
					} case _NMETHODCALL: {
						break;
					} case _NIDENTIFIER: {
						if(this->debug_evaluation)
					  		std::cout << "Expression at " << expr << " is a NIdentifier with value \"" << dynamic_cast<NIdentifier*>(expr)->_name << "\"" << std::endl;
						break;
					} case _NCOMPLEX: {
						if(this->debug_evaluation)
					  		std::cout << "Expression at " << expr << " is a NComplex with value " << dynamic_cast<NComplex*>(expr)->_c << std::endl;
						return &(dynamic_cast<NComplex*>(expr)->_c);
					} case _NSCALAR: {
					  	if(this->debug_evaluation)
					  		std::cout << "Expression at " << expr << " is a NScalar with value " << dynamic_cast<NScalar*>(expr)->_s << std::endl;
					  	return &(dynamic_cast<NScalar*>(expr)->_s);
					}
				}
				return nullptr;
			}

			Mt::core::IMtObject* EvaluationEngine::DoBinaryOperation(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs, yy::SMLParser::token_type oper, std::map<std::string, Mt::core::IMtObject>& GST) {
				switch(oper) {
					case yy::SMLParser::token_type::TPLUS: {
						if(this->debug_evaluation)
							std::cout << "NBinaryOperation is addition." << std::endl;
						return this->BinaryAdd(lhs, rhs);
					}
					case yy::SMLParser::token_type::TMINUS: {
						if(this->debug_evaluation)
							std::cout << "NBinaryOperation is subtraction." << std::endl;
						return this->BinaryMinus(lhs, rhs);
					}
					case yy::SMLParser::token_type::TMUL: {
						if(this->debug_evaluation)
							std::cout << "NBinaryOperation is multiplication." << std::endl;
						return this->BinaryMultiply(lhs, rhs);
					}
					case yy::SMLParser::token_type::TDIV: {
						if(this->debug_evaluation)
							std::cout << "NBinaryOperation is division." << std::endl;
						return this->BinaryDivied(lhs, rhs);
					}
				}
				return nullptr;
			}

			Mt::core::IMtObject* EvaluationEngine::BinaryAdd(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs) {
				switch(lhs->DerivedType) {
					case Mt::core::TYPE::SCALAR: {
						auto _lhs = dynamic_cast<Mt::objects::Scalar*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Scalar*>(rhs);
						auto retval = new Mt::objects::Scalar((*_lhs)+(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Addition result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::COMPLEX: {
						auto _lhs = dynamic_cast<Mt::objects::Complex*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Complex*>(rhs);
						auto retval = new Mt::objects::Complex((*_lhs)+(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Addition result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::MATRIX: {

					} case Mt::core::TYPE::SET: {

					} case Mt::core::TYPE::LIST: {
						break;
					}
				}
				return nullptr;
			}

			Mt::core::IMtObject* EvaluationEngine::BinaryMinus(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs) {
				switch(lhs->DerivedType) {
					case Mt::core::TYPE::SCALAR: {
						auto _lhs = dynamic_cast<Mt::objects::Scalar*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Scalar*>(rhs);
						auto retval = new Mt::objects::Scalar((*_lhs)-(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Subtraction result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::COMPLEX: {
						auto _lhs = dynamic_cast<Mt::objects::Complex*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Complex*>(rhs);
						auto retval = new Mt::objects::Complex((*_lhs)-(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Subtraction result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::MATRIX: {

					} case Mt::core::TYPE::SET: {

					} case Mt::core::TYPE::LIST: {
						break;
					}
				}
				return nullptr;
			}	

			Mt::core::IMtObject* EvaluationEngine::BinaryMultiply(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs) {
				switch(lhs->DerivedType) {
					case Mt::core::TYPE::SCALAR: {
						auto _lhs = dynamic_cast<Mt::objects::Scalar*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Scalar*>(rhs);
						auto retval = new Mt::objects::Scalar((*_lhs)*(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Multiplication result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::COMPLEX: {
						auto _lhs = dynamic_cast<Mt::objects::Complex*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Complex*>(rhs);
						auto retval = new Mt::objects::Complex((*_lhs)*(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Multiplication result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::MATRIX: {

					} case Mt::core::TYPE::SET: {

					} case Mt::core::TYPE::LIST: {
						break;
					}
				}
				return nullptr;
			}

			Mt::core::IMtObject* EvaluationEngine::BinaryDivied(Mt::core::IMtObject* lhs, Mt::core::IMtObject* rhs) {
				switch(lhs->DerivedType) {
					case Mt::core::TYPE::SCALAR: {
						auto _lhs = dynamic_cast<Mt::objects::Scalar*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Scalar*>(rhs);
						auto retval = new Mt::objects::Scalar((*_lhs)/(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Division result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::COMPLEX: {
						auto _lhs = dynamic_cast<Mt::objects::Complex*>(lhs);
						auto _rhs = dynamic_cast<Mt::objects::Complex*>(rhs);
						auto retval = new Mt::objects::Complex((*_lhs)/(*_rhs));
						if(this->debug_evaluation)
							std::cout << "Division result: " << retval << std::endl;
						return retval;
					} case Mt::core::TYPE::MATRIX: {

					} case Mt::core::TYPE::SET: {

					} case Mt::core::TYPE::LIST: {
						break;
					}
				}
				return nullptr;
			}

			void EvaluationEngine::PrintResult(Mt::core::IMtObject* res, std::string input) {
				switch(res->DerivedType) {
					case Mt::core::TYPE::SCALAR: {
						auto _res = dynamic_cast<Mt::objects::Scalar*>(res);
						std::cout << input << " = " << *_res << std::endl;
						delete _res;
						break;
					} case Mt::core::TYPE::COMPLEX: {
						auto _res = dynamic_cast<Mt::objects::Complex*>(res);
						std::cout << input << " = " << *_res << std::endl;
						delete _res;
						break;
					} case Mt::core::TYPE::MATRIX: {

					} case Mt::core::TYPE::SET: {

					} case Mt::core::TYPE::LIST: {
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
							auto vardec = dynamic_cast<NVariableDeclaration*>(statement);
							if(this->debug_evaluation)
								std::cout << "NVariableDeclaration with Identifier of \"" << vardec->_id._name << "\" " << std::endl;
							if(vardec->_assignmentExpr == nullptr) {

							} else {
								GST[vardec->_id._name] = *this->ProcessExpression(vardec->_assignmentExpr, GST);
								this->PrintResult(&GST[vardec->_id._name], rawInput);
							}
							break;
						} case _NEXPRESSIONSTATEMENT: {
							auto expr = dynamic_cast<NExpressionStatement*>(statement);
							if(this->debug_evaluation)
								std::cout << "Expression " << expr << " is of type " << this->GetNameFromMagik(expr->_expression.type) << std::endl;
							auto res = this->ProcessExpression(&(expr->_expression), GST);
							this->PrintResult(res, rawInput);
							break;
						} case _NFUNCTIONDECLARATION: {
							
							break;
						} case _NLISTDECLARATION: {
							
							break;
						} default:
							std::cerr << "Unknown statement type: " << this->GetNameFromMagik(statement->type) << std::endl;
					}
				}
			}
		}
	}
}
