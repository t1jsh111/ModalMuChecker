#include <iostream>
#include <filesystem>
#include <algorithm>
#include "Parser.h"
#include "Tokenizer.h"
#include <vector>
#include <cmath>
#include <iostream>
#include <sstream>

#include <istream>
#include <chrono>
#include "NestingDepthCalculator.h"
#include "AlternatingNestingDepthCalculator.h"
#include "NaiveAlgorithm.h"
#include "EmersonLeiAlgorithm.h"
#include "DependentAlternationDepthCalculator.h"






int main() {


    // Parse Labelled Transition System from file
    Lts lts(parser_space::Parser::parseLts("resources/dining/dining_5.aut"));
    // Parse formula
    auto form = parser_space::Parser::parseFormulaFile("resources/dining/invariantly_inevitably_eat.mcf");

    // Apply the naive algorithm on the LTS and see which states satisfy the formula
    const auto& solution = NaiveAlgorithm::evaluate(*form, lts);

    for(const auto& el : solution) {
        std::cout << "state " << el << std::endl;
    }

    // Apply the emerson-lei algorithm on the LTS and see which states satisfy the formula
    const auto& solution2 = EmersonLeiAlgorithm::evaluate(*form, lts);

    for(const auto& el : solution2) {
        std::cout << "state " << el << std::endl;
    }

    // Print the different types of depths of the formula
    std::cout << "Nesting depth: " << NestingDepthCalculator::computeNestingDepth(*form) << std::endl;
    std::cout << "Alternating nesting depth: " << AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(*form) << std::endl;
    std::cout << "Dependent alternating nesting depth: " << DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(*form) << std::endl;


    return 0;
}










