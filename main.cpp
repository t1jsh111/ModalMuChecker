#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Parser.h"
#include "Tokenizer.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <chrono>
#include "NestingDepthCalculator.h"
#include "AlternatingNestingDepthCalculator.h"
#include "NaiveAlgorithm.h"
#include "EmersonLeiAlgorithm.h"
#include "DependentAlternationDepthCalculator.h"

//using namespace std::chrono;
//
//enum Algorithm {Naive, EmersonLei};
//enum Data {States, Initial, Iterations, Milliseconds};
//
//std::string getFileName(const std::string& filePath) {
//    int lastSlashLocation = 0;
//    int nameLength = 0;
//
//    for(size_t i = filePath.size() - 1; i >= 0; i--) {
//        if(filePath[i] == '/') {
//            lastSlashLocation = i;
//            nameLength = filePath.size() - 1 - lastSlashLocation;
//            break;
//        }
//    }
//
//    return filePath.substr(lastSlashLocation+1,nameLength);
//}
//
//void testFolder(const std::string& folderPath, Algorithm alg, Data data) {
//
//    std::vector<std::string> formulas;
//    std::vector<std::string> transitionSystems;
//
//    for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(folderPath)) {
//        std::string fileLocation = dirEntry.path().string();
//
//        if(fileLocation.substr(fileLocation.size() - 4, 4) == ".mcf") {
//            formulas.push_back(fileLocation);
//        } else if (fileLocation.substr(fileLocation.size() - 4, 4) == ".aut") {
//            transitionSystems.push_back(fileLocation);
//        }
//    }
//
//    std::sort(formulas.begin(), formulas.end());
//    std::sort(transitionSystems.begin(), transitionSystems.end());
//
//
//
//    for(const auto& transitionSystem : transitionSystems) {
//        std::cout << "----" << transitionSystem << "----" << std::endl;
//        Lts lts(parser_space::Parser::parseLts(transitionSystem));
//        for(const auto& formula : formulas) {
//            auto form = parser_space::Parser::parseFormulaFile(formula);
//            std::unordered_set<int> solution = std::unordered_set<int>();
//            int iterations = 0;
//            high_resolution_clock::time_point t1;// = high_resolution_clock::now();
//            high_resolution_clock::time_point t2;// = high_resolution_clock::now();
//            double avg_time_span = 0;
//            int loop_bound = 5;
//
//            for (int i = 0; i < loop_bound; i++) {
//                switch (alg) {
//                    case Algorithm::Naive: {
//                        t1 = high_resolution_clock::now();
//                        solution = NaiveAlgorithm::evaluate(*form, lts);
//                        t2 = high_resolution_clock::now();
//                        iterations = NaiveAlgorithm::numberOfIterations;
//                        break;
//                    }
//                    case Algorithm::EmersonLei: {
//                        t1 = high_resolution_clock::now();
//                        solution = EmersonLeiAlgorithm::evaluate(*form, lts);
//                        t2 = high_resolution_clock::now();
//                        iterations = EmersonLeiAlgorithm::numberOfIterations;
//                        break;
//                    }
//                }
//                avg_time_span += duration_cast<milliseconds>(t2 - t1).count();
//
//                if (data != Milliseconds) {
//                    break;
//                }
//            }
//
//            std::cout << getFileName(formula) << " = ";
//            switch(data) {
//                case States: {
//                    std::cout << "{ ";
//                    for(const auto& el : solution) {
//                        std::cout << el << ", ";
//                    }
//                    std::cout << "}" << std::endl;
//                    break;
//                }
//                case Initial: {
//                    if(solution.find(lts.initialState) != solution.end()) {
//                        std::cout << "true" << std::endl;
//                        break;
//                    }
//                    std::cout << "false" << std::endl;
//                    break;
//                }
//                case Iterations: {
//                    std::cout << iterations << " iterations" << std::endl;
//                    break;
//                }
//                case Milliseconds: {
//                    std::cout << avg_time_span/loop_bound << " milliseconds" << std::endl;
//                    break;
//                }
//            }
//        }
//    }
//}



int count_digit(int number) {
    return std::to_string(number).size();
}

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



    for(const auto& formula : formulas) {
        std::cout << std::endl;
        std::cout << "=====" << formula << "====" << std::endl;

        for(const auto& transitionSystem : transitionSystems) {
            std::cout << "----" << transitionSystem << "----" << std::endl;

            Lts lts(parser_space::Parser::parseLts(transitionSystem));
            auto form = parser_space::Parser::parseFormulaFile(formula);

            auto start = std::chrono::high_resolution_clock::now();
            const auto& solution = NaiveAlgorithm::evaluate(*form, lts);
            auto end = std::chrono::high_resolution_clock::now();

            std::cout << getFileName(formula) << " = " << std::endl;
            std::cout << "No of states: " << solution.size() << std::endl;

//            for(const auto& el : solution) {
//                std::cout << el << ", ";
//
//            }
//            std::cout << "}" << std::endl;
            std::cout << "Initial state satisfies formula: " <<
                (solution.find(lts.getInitialState()) != solution.end() ? "Yes" : "No") << std::endl;

            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
            std::cout << "Naive Algo exectime: " << duration.count() << " milisec" << std::endl;
            std::cout << "                   = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsec" << std::endl;
            std::cout << "Naive algo fix-iterations: " << NaiveAlgorithm::numberOfIterations << std::endl;

            start = std::chrono::high_resolution_clock::now();
            const auto& solutionEmerson = EmersonLeiAlgorithm::evaluate(*form, lts);
            end = std::chrono::high_resolution_clock::now();

            auto durationEmerson = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
            std::cout << "Emerson Algo exectime: " << durationEmerson.count() << " milisec" << std::endl;
            std::cout << "                   = " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microsec" << std::endl;
            std::cout << "Emerson algo fix-iterations: " << EmersonLeiAlgorithm::numberOfIterations << std::endl;
            std::cout << std::endl;

        }
        std::cout << "================" << std::endl;
    }

}


void printDepths(const std::string& folderPath) {
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



    for(const auto& formula : formulas) {
        std::cout << "---Formula: " << formula << "----" << std::endl;
        auto form = parser_space::Parser::parseFormulaFile(formula);
        std::cout << "Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*form) << std::endl;
        std::cout << "Alternating nesting depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*form) << std::endl;
        std::cout << "Dependent alternating nesting depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*form) << std::endl;
        std::cout << std::endl;
    }
}



int main() {

    std::string filePath = "resources/additional/";


    //printDepths(filePath);
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
