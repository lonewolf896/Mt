/*
    SParser.cc - Implementation for a basic scanning parser
*/

#include "core/lang/SParser.hh"

namespace Mt {
    SParser* SParser::instance = nullptr;
    
    SParser::SParser(void) {
        std::cout << "Warning: Using Simple Parser, simple math only" << std::endl;
    }

    SParser::~SParser(void) {
    
    }

    SParser* SParser::GetInstance(void) {
        if(SParser::instance == nullptr)
            return (SParser::instance = new SParser());
        return SParser::instance;
    }

    void SParser::Eval(std::string expr) {
        // This is used to match things like 54+5 and 65-2,
        // std::regex expr_match("([0-9]{1,11}[+-/\\*][0-9]{1,11})",  std::regex_constants::ECMAScript);
        
        // Really shi... I mean janky, yeah,  parsing incoming.
        // Reads from left to right, attempts to match 2 symbols like 44+2 and then evals on the spot,
        // After that it starts from the eval result and continues until the end of the expression string
        
        // attempt to force copy and give us a mutable expression
        std::string MutableExpression(expr);
        std::string Operand;
        bool OperandSwitch = false;
        Expression exp;
        for(auto _m : MutableExpression) {
            const char * m = &_m;
             if(!OperandSwitch) {
                if(strncmp(m, "+", 1)) {
                    exp.Oper = ADD;
                    OperandSwitch = true;
                } else if(strncmp(m, "-", 1)) {
                    exp.Oper = SUB;
                    OperandSwitch = true;
                } else if(strncmp(m, "/", 1)) {
                    exp.Oper = DIV;
                    OperandSwitch = true;
                } else if(std::strncmp(m, "*", 1)) {
                    exp.Oper = MUL;
                    OperandSwitch = true;
                    try {
                        exp.LeftOperand = std::stold(Operand);   
                    } catch (const std::invalid_argument& ia) { 
                        std::cout << "Invalid Argument: " << ia.what() << std::endl;
                    }
                } else if(strncmp(m, " ", 1)) {
                    // Do nothing
                } else {
                    // If it is anything else
                    Operand += m;
                }
             } else {
                
             }
        }

    }
}
