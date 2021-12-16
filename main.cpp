#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Parser.h"
#include "Tokenizer.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>
#include "DataPrinter.h"
#include <istream>
#include <chrono>
#include "NestingDepthCalculator.h"
#include "AlternatingNestingDepthCalculator.h"
#include "NaiveAlgorithm.h"
#include "EmersonLeiAlgorithm.h"
#include "DependentAlternationDepthCalculator.h"









int main() {


    std::cout << "Welcome to the ModelMuChecker!" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 1 to compute all information of a folder containing transitionsystems and formulas";
    std::cout << "-----" << std::endl;
    std::cout << "Press 2 to compute all" << std::endl;
    std::cout << "-----" << std::endl;

    std::string filePath = "resources/demanding/";
    //auto form = parser_space::Parser::parseFormulaFile("resources/demanding/questions_can_be_answered.mcf");
//    auto form = parser_space::Parser::parseFormulaFile("resources/demanding/questions_will_be_answered.mcf");
//    form->printFormula();




    DataPrinter printer;
    printer.printTables("resources/demanding");



    return 0;
}


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




void printDepths(const std::string& folderPath) {
    std::vector<std::string> formulas;
    std::vector<std::string> transitionSystems;

    for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(folderPath)) {
        std::string fileLocation = dirEntry.path().generic_string();

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



void testFolder(const std::string& folderPath) {

    std::vector<std::string> formulas;
    std::vector<std::string> transitionSystems;

    for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(folderPath)) {
        std::string fileLocation = dirEntry.path().generic_string();

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