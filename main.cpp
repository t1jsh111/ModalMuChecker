#include <iostream>
#include "parsing/Parser.h"
#include "parsing/Tokenizer.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    //Lts lts(Parser::parseLts("resources/testcases/boolean/test.aut"));
//    std::cout << "address after returning" << &(lts.startStateToTransitions) << std::endl;
//    std::cout << "nr of states " << lts.getNrOfStates();
    //lts.printTransitionsOfStartState(0);
    //lts.printTransitionsOfEndState(2);

    //Parser::parseFormulaFile("resources/testcases/combined/form5.mcf");
    parser_space::Tokenizer tokenizer;
    std::vector<parser_space::Token> vec = tokenizer.parse("nu X. (<tau>X && mu Y. (<tau>Y || [a]false))");
    for(auto token : vec) {
        token.debugPrint();
    }





    return 0;
}
