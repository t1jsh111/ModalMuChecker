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





std::string getInput(std::unordered_set<std::string> recognizedCommands) {
    std::string inputWord;
    while(std::cin >> inputWord) {
        bool inputRecognized = recognizedCommands.find(inputWord) != recognizedCommands.end();

        if(inputRecognized) {
            return inputWord;
        } else {
            std::cout << "input " << inputWord << " is not valid input please try again " << std::endl;
        }

    }
    return inputWord;
}

void printMenu() {
    std::cout << "Welcome to the ModelMuChecker!" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 1 to compute all information of a folder containing transitionsystems and print in Console format" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 2 to compute all information of a folder containing transitionsystems and print in LaTeX format" << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "Press 3 to compute for a specific transition system, and specific formula type, using a specific algorithm" << std::endl;
    std::cout << "-----" << std::endl;
}



int main() {

    std::cout << "   _____             .___      .__       _____   ____ ___ \n"
                 "  /     \\   ____   __| _/____  |  |     /     \\ |    |   \\\n"
                 " /  \\ /  \\ /  _ \\ / __ |\\__  \\ |  |    /  \\ /  \\|    |   /\n"
                 "/    Y    (  <_> ) /_/ | / __ \\|  |__ /    Y    \\    |  / \n"
                 "\\____|__  /\\____/\\____ |(____  /____/ \\____|__  /______/  \n"
                 "        \\/            \\/     \\/               \\/          \n"
                 "_________ .__                   __                        \n"
                 "\\_   ___ \\|  |__   ____   ____ |  | __ ___________        \n"
                 "/    \\  \\/|  |  \\_/ __ \\_/ ___\\|  |/ // __ \\_  __ \\       \n"
                 "\\     \\___|   Y  \\  ___/\\  \\___|    <\\  ___/|  | \\/       \n"
                 " \\______  /___|  /\\___  >\\___  >__|_ \\\\___  >__|          \n"
                 "        \\/     \\/     \\/     \\/     \\/    \\/              \n"
                 "                                                          \n"
                 "                                                          \n";
    std::cout << "By Tijs H. and Milan H." << std::endl;

    DataPrinter dataPrinter;

    while(true) {
        printMenu();


        std::string inputWord = getInput({"1", "2", "3"});

        if (inputWord == "1") {
            std::cout << "drag and drop folder to console / provide folder path and press enter" << std::endl;
            std::cin >> inputWord;
            try {
                dataPrinter.printTablesTerminalOutput(inputWord);
            } catch (const std::exception &e) {
                std::cout << "it looks like the folder contains invalid formulas/lts" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }

        } else if (inputWord == "2") {
            std::cout << "drag and drop folder to console / provide folder path and press enter" << std::endl;
            std::cin >> inputWord;
            try {
                dataPrinter.printTables(inputWord);
            } catch (const std::exception &e) {
                std::cout << "it looks like the folder contains invalid formulas/lts" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }
        } else if (inputWord == "3") {
            std::cout << "drag and drop transition system to console / provide file path and press enter" << std::endl;
            std::cin >> inputWord;
            try {
                auto lts = parser_space::Parser::parseLts(inputWord);

                enterFormula:

                std::cout << "drag and drop the formula to console / provide file path and press enter" << std::endl;
                std::cin >> inputWord;
                try {
                    auto form = parser_space::Parser::parseFormulaFile(inputWord);
                    std::cout << "press n for executing the naive algorithm: " << std::endl;
                    std::cout << "press e for executing the emerson algorithm: " << std::endl;
                    inputWord = getInput({"n", "e"});
                    if (inputWord == "n") {
                        dataPrinter.printInformationSingleFormulaAndLts(*form, lts, DataPrinter::Naive);
                    } else if (inputWord == "e") {
                        dataPrinter.printInformationSingleFormulaAndLts(*form, lts, DataPrinter::Emerson);
                    } else {
                        throw std::runtime_error("This should not be reachable. Bug in code!!");
                    }


                } catch (const std::exception &e) {
                    std::cout << "it looks like the formula is not properly formatted" << std::endl;
                    std::cout << e.what() << std::endl;
                    std::cout << "Please try again";

                    // This is really bad practice, but okay for a functional interface for now...
                    goto enterFormula;
                }

            } catch (const std::exception &e) {
                std::cout << "it looks like the lts is not properly formatted" << std::endl;
                std::cout << e.what() << std::endl;
                std::cout << "Please try again";
                continue;
            }

        } else {
            throw std::runtime_error("This should not be reachable. Bug in code!!");
        }
    }


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