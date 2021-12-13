#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Parser.h"
#include "Tokenizer.h"
#include <vector>
#include <iostream>
#include "NestingDepthCalculator.h"
#include "AlternatingNestingDepthCalculator.h"
#include "NaiveAlgorithm.h"
#include "EmersonLeiAlgorithm.h"
#include "DependentAlternationDepthCalculator.h"

std::string getFileName(const std::string& filePath) {
    int lastSlashLocation = 0;
    int nameLength = 0;

    for(size_t i = filePath.size() - 1; i >= 0; i--) {
        if(filePath[i] == '/') {
            lastSlashLocation = i;
            nameLength = filePath.size() - 1 - lastSlashLocation;
            break;
        }
    }

    return filePath.substr(lastSlashLocation+1,nameLength);
}

void testFolder(const std::string& folderPath) {

    std::vector<std::string> formulas;
    std::vector<std::string> transitionSystems;

    for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(folderPath)) {
        std::string fileLocation = dirEntry.path();

        if(fileLocation.substr(fileLocation.size() - 4, 4) == ".mcf") {
            formulas.push_back(fileLocation);
        } else if (fileLocation.substr(fileLocation.size() - 4, 4) == ".aut") {
            transitionSystems.push_back(fileLocation);
        }
    }

    std::sort(formulas.begin(), formulas.end());
    std::sort(transitionSystems.begin(), transitionSystems.end());



    for(const auto& transitionSystem : transitionSystems) {
        std::cout << "----" << transitionSystem << "----" << std::endl;
        Lts lts(parser_space::Parser::parseLts(transitionSystem));
        for(const auto& formula : formulas) {
            auto form = parser_space::Parser::parseFormulaFile(formula);
            const auto& solution = NaiveAlgorithm::evaluate(*form, lts);
            std::cout << getFileName(formula) << " = ";
            std::cout << "{ ";
            for(const auto& el : solution) {
                std::cout << el << ", ";
            }
            std::cout << "}" << std::endl;
        }
    }

}

int main() {

    std::string filePath = "resources/testcases/fixpoints_only/";
    testFolder(filePath);
//    std::cout << "-----" << std::endl;


//    Lts lts(parser_space::Parser::parseLts("resources/testcases/modal_operators/test.aut"));


//    for(int i = 1; i < 6; i++) {
//        //std::cout << "resources/testcases/boolean/form" + std::to_string(i) + ".mcf";
//        auto form = parser_space::Parser::parseFormulaFile("resources/testcases/modal_operators/form" + std::to_string(i) + ".mcf");
//        const auto& solution = NaiveAlgorithm::evaluate(*form, lts);
//        std::cout << "form" << i << ": ";
//        std::cout << "{ ";
//        for(const auto& el : solution) {
//             std::cout << el << ", ";
//        }
//        std::cout << "}" << std::endl;
//    }

//    const auto& solution = NaiveAlgorithm::evaluate(*form, lts);
//
//    for(const auto& el : solution) {
//        std::cout << "state " << el << std::endl;
//    }



//    std::cout << std::endl;
//    std::cout << "number of iterations: " << NaiveAlgorithm::numberOfIterations << std::endl;
//
//    std::cout << "----second solution----" << std::endl;
//
//    const auto& solution2 = EmersonLeiAlgorithm::evaluate(*form, lts);
//    for(const auto& el : solution2) {
//        std::cout << "state " << el << std::endl;
//    }
//    std::cout << "number of iterations: " << EmersonLeiAlgorithm::numberOfIterations;


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
//
//
//
//    std::cout << "Equality check: first " << &minFix[0] << "second" << &form;
//
//    auto slideExample1 = parser_space::Parser::parseFormula("(mu A. nu B. (A || B) && mu C. mu D. (C && mu E. (true || E)))");
//    slideExample1->printFormula();
//    std::cout << std::endl;
//    std::cout << "Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*slideExample1) << std::endl;
//    std::cout << "Alternating depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*slideExample1) << std::endl;
//    std::cout << "depending alternating depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*slideExample1) << std::endl;
//
//
//    auto slideExample2 = parser_space::Parser::parseFormula("(mu A. nu B. (A || B) && mu C. nu D. (C && mu E. (true || E)))");
//    slideExample2->printFormula();
//    std::cout << std::endl;
//    std::cout << "Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*slideExample2) << std::endl;
//    std::cout << "Alternating depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*slideExample2) << std::endl;
//    std::cout << "depending alternating depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*slideExample2) << std::endl;
//
//    form = parser_space::Parser::parseFormulaFile("resources/testcases/boolean/form9.mcf");
//    Lts test(parser_space::Parser::parseLts("resources/testcases/boolean/test.aut"));
//
//    std::unordered_map<FixedPointVariable, std::unordered_set<int>, FixedPointVariable::HashFunction> A;
//    std::unordered_set<int> result = NaiveAlgorithm::evaluate(*form, test, A);
//    for (int i : result) {
//        std::cout << "vertex: " << i << std::endl;
//    }
//
//    auto testFormula = parser_space::Parser::parseFormula("mu X. mu X. X");
//    testFormula->printFormula();
//    auto variables = testFormula->getFixedPointVariables();
//    auto firstVariable = variables.back().get();
//
//    auto theFormula = testFormula->getMinFixedPointFormulas().at(0);
//    bool theSame = firstVariable == theFormula.get().getMFixedPointVariable();
//    std::cout << "they are " << ( theSame ? "the same" : "not the same");

    return 0;
}
