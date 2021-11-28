#include <iostream>
#include "parsing/Parser.h"
#include <vector>

int main() {
    std::cout << "Hello, World!" << std::endl;

    //Lts lts(Parser::parseLts("resources/testcases/boolean/test.aut"));
//    std::cout << "address after returning" << &(lts.startStateToTransitions) << std::endl;
//    std::cout << "nr of states " << lts.getNrOfStates();
    //lts.printTransitionsOfStartState(0);
    //lts.printTransitionsOfEndState(2);
    Parser::parseFormulaFile("resources/testcases/combined/form5.mcf");




    return 0;
}
