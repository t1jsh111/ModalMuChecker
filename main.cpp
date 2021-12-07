#include <iostream>
#include "Parser.h"
#include "Tokenizer.h"
#include <vector>
#include <iostream>
#include "NestingDepthCalculator.h"
#include "AlternatingNestingDepthCalculator.h"
#include "DependentAlternationDepthCalculator.h"


int main() {

    Lts lts(parser_space::Parser::parseLts("resources/testcases/boolean/test.aut"));
    std::cout << "nr of states " << lts.getNrOfStates() << std::endl;
    lts.printTransitionsOfStartState(0);
    lts.printTransitionsOfEndState(2);

    std::cout << std::endl;

    auto form = parser_space::Parser::parseFormulaFile("resources/testcases/fixpoints_only/form5.mcf");
    form->printFormula();
    std::cout << std::endl;
    auto minFix = form->getMaxFixedPointFormulas();


//    std::cout << "------------" << std::endl;
//    auto slideExample1 = parser_space::Parser::parseFormula("(nu X. mu Y. nu Z. (X || Y) && nu X. mu Y. nu Z. (X || Y))");
//
//    auto maxFix = slideExample1->getMaxFixedPointFormulas();
//    slideExample1->printFormula();
//    std::cout << std::endl;
//
//
//
//    for(const auto& form : maxFix) {
//        std::cout << " subformula: " ;
//        form.get().printFormula();
//        std::cout << std::endl;
//
//        const auto& freevars = form.get().getFreeFixedPointVariables();
//        std::cout << "free fixed point variables" << std::endl;
//        for(const auto& freevar : freevars) {
//            freevar.get().printFormula();
//        }
//        std::cout << std::endl;
//
//        const auto& allvars = form.get().getFixedPointVariables();
//        std::cout << "free fixed point variables" << std::endl;
//        for(const auto& var : allvars) {
//            var.get().printFormula();
//        }
//        std::cout << std::endl;
//
//        std::cout << "address form" << &form.get() << std::endl;
//    }



    std::cout << "Equality check: first " << &minFix[0] << "second" << &form;

    auto slideExample1 = parser_space::Parser::parseFormula("(mu A. nu B. (A || B) && mu C. mu D. (C && mu E. (true || E)))");
    slideExample1->printFormula();
    std::cout << std::endl;
    std::cout << "Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*slideExample1) << std::endl;
    std::cout << "Alternating depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*slideExample1) << std::endl;
    std::cout << "depending alternating depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*slideExample1) << std::endl;


    auto slideExample2 = parser_space::Parser::parseFormula("(mu A. nu B. (A || B) && mu C. nu D. (C && mu E. (true || E)))");
    slideExample2->printFormula();
    std::cout << std::endl;
    std::cout << "Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*slideExample2) << std::endl;
    std::cout << "Alternating depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*slideExample2) << std::endl;
    std::cout << "depending alternating depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*slideExample2) << std::endl;



    return 0;
}
