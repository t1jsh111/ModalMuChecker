#include <iostream>
#include "parsing/inc/Parser.h"
#include "parsing/inc/Tokenizer.h"
#include <vector>
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    Lts lts(parser_space::Parser::parseLts("resources/testcases/boolean/test.aut"));
    std::cout << "nr of states " << lts.getNrOfStates() << std::endl;
    lts.printTransitionsOfStartState(0);
    lts.printTransitionsOfEndState(2);

    parser_space::Parser::parseFormulaFile("resources/testcases/combined/form5.mcf");






    return 0;
}
