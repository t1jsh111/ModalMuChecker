//
// Created by Tijs Hoeijmakers on 15/12/2021.
//

#include "DataPrinter.h"
#include "EmersonLeiAlgorithm.h"
#include "NaiveAlgorithm.h"
#include "NaturalSort.h"
#include "Lts.h"
#include "Parser.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include "NestingDepthCalculator.h"
#include "AlternatingNestingDepthCalculator.h"
#include "DependentAlternationDepthCalculator.h"
#include <filesystem>

void DataPrinter::printNumberOfFixedPoints(std::string folderPath) {

}


void DataPrinter::printTimingTable(std::string folderPath) {

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

    std::sort(formulas.begin(), formulas.end(), SI::natural::compare<std::string>);
    std::sort(transitionSystems.begin(), transitionSystems.end(), SI::natural::compare<std::string>);



    for(const auto& formula : formulas) {
        std::cout << std::endl;
        std::cout << "=====" << getFileName(formula) << "====" << std::endl;
        std::vector<std::string> line1;
        std::vector<std::string> line2;
        std::vector<std::string> line3;


        for(const auto& transitionSystem : transitionSystems) {
            std::string fileName = getFileName(transitionSystem);
            fileName = ReplaceAll(fileName, "_", "\\_");
            fileName = ReplaceAll(fileName, ".aut", "");

            line1.push_back(" & " + fileName);

            Lts lts(parser_space::Parser::parseLts(transitionSystem));
            auto form = parser_space::Parser::parseFormulaFile(formula);

            auto start = std::chrono::high_resolution_clock::now();
            const auto& solution = NaiveAlgorithm::evaluate(*form, lts);
            auto end = std::chrono::high_resolution_clock::now();



            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
            double dur = (double) duration.count() / 1000;
            std::string durStr = std::to_string(dur);
            durStr.erase ( durStr.find_last_not_of('0') + 1, std::string::npos );
            line2.push_back(durStr);


            start = std::chrono::high_resolution_clock::now();
            const auto& solutionEmerson = EmersonLeiAlgorithm::evaluate(*form, lts);
            end = std::chrono::high_resolution_clock::now();

            auto durationEmerson = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
            dur = (double) durationEmerson.count() / 1000;
            durStr = std::to_string(dur);
            durStr.erase ( durStr.find_last_not_of('0') + 1, std::string::npos );
            line3.push_back(durStr);

        }

        printLines(line1, line2, line3);

        std::cout << "================" << std::endl;
    }
}

void DataPrinter::printLines(std::vector<std::string> line1, std::vector<std::string> line2, std::vector<std::string> line3) {
    int numberOfTables = std::ceil( (double) line1.size() / 5 );
    for(int i = 0; i < numberOfTables; i++) {
        std::cout << "\\resizebox{\\textwidth}{!}{" << std::endl;
        std::cout << "\\begin{tabular}{|c|c|c|c|c|c|}\\hline" << std::endl;

        std::cout << " ";
        for(int j = i*5; j - (i*5) < 5; j++) {
            int index = std::min(j, (int) line1.size() - 1);
//
//            if ((index % 5) == 0) {
//                std::cout << " ";
//            }
            std::cout << line1[index];

        }
        std::cout << "\\\\\\hline" << std::endl;

        std::cout << "\\textbf{Naive}";
        for(int j = i*5; j - (i*5) < 5; j++) {
            int index = std::min(j, (int) line1.size() - 1);

//            if ((index % 5) == 0) {
//                std::cout << "\\textbf{Naive}";
//            }
            std::cout << " & " << line2[index];

        }
        std::cout << "\\\\\\hline" << std::endl;

        std::cout << "\\textbf{Emerson}";
        for(int j = i*5; j - (i*5) < 5; j++) {
            int index = std::min(j, (int) line1.size() - 1);
//            if ((index % 5) == 0) {
//                std::cout << "\\textbf{Emerson}";
//            }
            std::cout << " & " << line3[index];

        }
        std::cout << "\\\\\\hline" << std::endl;

        std::cout << "\\end{tabular}" << std::endl;
        std::cout << "}" << std::endl;
    }

}

std::string DataPrinter::getFileName(const std::string &filePath) {
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

std::string DataPrinter::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

void DataPrinter::printTables(std::string folderPath) {

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

    std::sort(formulas.begin(), formulas.end(), SI::natural::compare<std::string>);
    std::sort(transitionSystems.begin(), transitionSystems.end(), SI::natural::compare<std::string>);



    for(const auto& formula : formulas) {
        std::cout << std::endl;
        std::cout << "%=====" << getFileName(formula) << "====" << std::endl;


        std::vector<std::string> timingLine1;
        std::vector<std::string> timingLine2;
        std::vector<std::string> timingLine3;

        std::vector<std::string> iterationsLine1;
        std::vector<std::string> iterationsLine2;
        std::vector<std::string> iterationsLine3;

        std::vector<std::string> initSat1;
        std::vector<std::string> initSat2;
        std::vector<std::string> initSat3;

        auto form = parser_space::Parser::parseFormulaFile(formula);


        for(const auto& transitionSystem : transitionSystems) {
            std::string fileName = getFileName(transitionSystem);
            fileName = ReplaceAll(fileName, "_", "\\_");
            fileName = ReplaceAll(fileName, ".aut", "");

            timingLine1.push_back(" & " + fileName);
            iterationsLine1.push_back(" & " + fileName);
            initSat1.push_back(" & " + fileName);

            Lts lts(parser_space::Parser::parseLts(transitionSystem));


            auto start = std::chrono::high_resolution_clock::now();
            const auto& solution = NaiveAlgorithm::evaluate(*form, lts);
            auto end = std::chrono::high_resolution_clock::now();



            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            double dur = (double) duration.count() / 1000;
            std::string durStr = std::to_string(dur);
            durStr.erase ( durStr.find_last_not_of('0') + 1, std::string::npos );
            timingLine2.push_back(durStr);
            iterationsLine2.push_back(std::to_string(NaiveAlgorithm::numberOfIterations));

            bool holdsForInitialState = solution.find(lts.getInitialState()) != solution.end();
            initSat2.push_back( (holdsForInitialState ? "Yes" : "No"));



            start = std::chrono::high_resolution_clock::now();
            const auto& solutionEmerson = EmersonLeiAlgorithm::evaluate(*form, lts);
            end = std::chrono::high_resolution_clock::now();

            auto durationEmerson = std::chrono::duration_cast<std::chrono::microseconds>(end-start);
            dur = (double) durationEmerson.count() / 1000;
            durStr = std::to_string(dur);
            durStr.erase ( durStr.find_last_not_of('0') + 1, std::string::npos );
            timingLine3.push_back(durStr);
            iterationsLine3.push_back(std::to_string(EmersonLeiAlgorithm::numberOfIterations));

            holdsForInitialState = solutionEmerson.find(lts.getInitialState()) != solution.end();
            initSat3.push_back( (holdsForInitialState ? "Yes" : "No"));

        }

        std::cout << "\\paragraph{Initial state}~\\\\" << std::endl;
        printLines(initSat1, initSat2, initSat3);



        std::cout << "\\paragraph{Performance in number of iterations}"
        << "checking number of iterations gives the following results\\\\" << std::endl;
        printLines(iterationsLine1, iterationsLine2, iterationsLine3);

        std::cout << "\\paragraph{Performance in time}"
        << "Checking the performance in time gives the following results in \\emph{milliseconds}:\\\\" << std::endl;
        printLines(timingLine1, timingLine2, timingLine3);

        std::cout << "\\paragraph{Depths:}" <<std::endl;
        std::cout << "\\begin{itemize}" << std::endl;
        std::cout << "\\item Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*form) << std::endl;
        std::cout << "\\item Alternating nesting depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*form) << std::endl;
        std::cout << "\\item Dependent alternating nesting depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*form) << std::endl;
        std::cout << "\\end{itemize}" << std::endl;

        std::cout << "%================" << std::endl;
    }
}
