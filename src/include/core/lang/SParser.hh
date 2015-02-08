/*
    SParser.hh - Definition for the scanning parser
*/
#pragma once
#include <utility>
#include <iostream>
#include <string>
#include <regex>
#include <cstring>
namespace Mt {
    class SParser {
        private:
            SParser(void);
            ~SParser(void);
            static SParser* instance;
        

            // Some internal types for expression evaluation
            typedef enum opers {
                ADD,
                MUL,
                DIV,
                SUB,
                MOD
            } Operator;
            
            typedef struct expr_t {
                long double LeftOperand;
                long double RightOperand;
                Operator Oper;
                long double Result;
            } Expression, *PExpression;

            

        public:
            static SParser* GetInstance(void);

            void Eval(std::string expr);
    };
}
