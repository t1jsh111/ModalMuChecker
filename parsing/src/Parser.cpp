//
// Created by tijsh on 26-11-2021.
//

#include "Parser.h"
#include "Formula.h"
#include <iostream>
#include <sstream>
#include <memory>

namespace parser_space {

    Lts Parser::parseLts(const std::string &filePath) {
        std::ifstream autFile(filePath);

        if (!autFile.is_open()) {
            std::cout << "Error: could not open the provided file...";
        }


        std::string currentWord;
        autFile >> currentWord;
        // The first word of a .aut file should always contain des
        if (currentWord != "des") {
            return Lts(0, 0, 0);
        }


        autFile >> currentWord; // currentWord gets assigned the tuple after 'des'
        int firstState = std::stoi(getElementOfTuple(currentWord, 0));
        int nrOfTransitions = std::stoi(getElementOfTuple(currentWord, 1));
        int nrOfStates = std::stoi(getElementOfTuple(currentWord, 2));

        Lts lts(firstState, nrOfTransitions, nrOfStates);


        // Add transitions to the lts
        while (autFile >> currentWord) {

            int startState = std::stoi(getElementOfTuple(currentWord, 0));
            std::string label = getElementOfTuple(currentWord, 1);
            int endState = std::stoi(getElementOfTuple(currentWord, 2));

            lts.addTransition(startState, label, endState);
        }


        return lts;
    }

/**
 *
 * @param tuple: a tuple in string form
 * @param index: 0 <= index < nrOfElements(index)
 * @return element at index of tuple represented as string
 */
    std::string Parser::getElementOfTuple(std::string tuple, int index) {
        int currentIndex = 0;
        int beginOfCurrentIndex = 1;
        std::string returnString = "";

        if (tuple.at(0) != '(' || tuple.at(tuple.length() - 1) != ')') {
            std::runtime_error("This is not a tuple!!");
            return "";
        }

        for (int i = 1; i < tuple.length() - 1; i++) {
            if (tuple.at(i) == ',') {
                currentIndex++;
                continue;
            }

            if (currentIndex == index) {
                returnString.push_back(tuple.at(i));
            }

        }

        if (currentIndex < index) {
            throw std::runtime_error("Index out of tuple boundary");
            return "";
        }

        return returnString;
    }


    std::shared_ptr<Formula> Parser::parseFormulaFile(const std::string &filePath) {
        std::ifstream formulaFile(filePath);

        if (!formulaFile.is_open()) {
            throw std::runtime_error("could not read the formula input file...");
        }
        std::stringstream buffer;
        buffer << formulaFile.rdbuf();

        const std::string str = buffer.str();

        Tokenizer tokenizer;


        auto tokenized = tokenizer.parse(str);

        return parseFormula(tokenized);
    }

    std::shared_ptr<Formula> Parser::parseFormula(const std::string& formula) {
        Tokenizer tokenizer;
        std::map<char, std::shared_ptr<FixedPointVariable>> environment;
        auto tokenized = tokenizer.parse(formula);

        return parseFormula(tokenized);
    }

    std::shared_ptr<Formula> Parser::parseFormula(std::vector<Token> &tokens) {
        size_t position = 0;
        std::map<char, std::shared_ptr<FixedPointVariable>> environment;
        return parseFormula(tokens, position, environment);
    }

    std::shared_ptr<Formula> Parser::parseFormula(std::vector<Token> &tokens, size_t &startPosition, std::map<char, std::shared_ptr<FixedPointVariable>>& environment) {
        for (auto &i = startPosition; i < tokens.size(); i++) {
            const auto &token = tokens[i];

            switch (token.mType) {
                case TRUE_LITERAL:
                    return std::make_shared<True>();
                    break;
                case FALSE_LITERAL:
                    return std::make_shared<False>();
                    break;
                case RECURSION_VARIABLE:
                    if(!environment.at(token.mText[0])) {
                        throw std::runtime_error("FOUND VARIABLE THAT IS NOT BOUND BY A FIXED POINT");
                    }
                    return environment.at(token.mText[0]);
                    break;
                case LEFT_ROUND_BRACKET: {
                    auto leftFormula = parseFormula(tokens, ++i, environment);
                    i++;
                    if (not(tokens[i].mType == AND_OPERATOR || tokens[i].mType == OR_OPERATOR)) {
                        throw std::runtime_error("No binary operator in logical formula");
                    }
                    // By if statement guaranteed tokens[i].mType is AND_OPERATOR or OR_OPERATOR
                    std::shared_ptr<Formula> logicalFormula;
                    if (tokens[i].mType == AND_OPERATOR) {
                        auto rightFormula = parseFormula(tokens, ++i, environment);
                        logicalFormula = std::make_shared<Conjunction>(leftFormula, rightFormula);
                    } else {
                        auto rightFormula = parseFormula(tokens, ++i, environment);
                        logicalFormula = std::make_shared<Disjunction>(leftFormula, rightFormula);
                    }
                    i++;
                    if (tokens[i].mType != RIGHT_ROUND_BRACKET) {
                        throw std::runtime_error("( bracket is not closed");
                    }
                    return logicalFormula;
                    break;
                }
                case MU_LITERAL: {
                    i++;
                    if (tokens[i].mType != RECURSION_VARIABLE) {
                        throw std::runtime_error("mu formula without being followed by recursion variable");
                    }
                    char fixedPointChar = tokens[i].mText[0];
                    auto fixedPointVariable = std::shared_ptr<FixedPointVariable>(
                            new FixedPointVariable(fixedPointChar));

                    environment[fixedPointChar] = fixedPointVariable;

                    auto formula = parseFormula(tokens, ++i, environment);
                    auto minFixedPointFormula = std::make_shared<MinFixedPoint>(fixedPointVariable, formula);
                    fixedPointVariable->setBoundingFormula(minFixedPointFormula);
                    return minFixedPointFormula;
                    break;
                }
                case NU_LITERAL: {
                    i++;
                    if (tokens[i].mType != RECURSION_VARIABLE) {
                        throw std::runtime_error("nu formula without being followed by recursion variable");
                    }
                    char fixedPointChar = tokens[i].mText[0];

                    auto fixedPointVariable = std::shared_ptr<FixedPointVariable>(
                            new FixedPointVariable(tokens[i].mText[0]));

                    environment[fixedPointChar] = fixedPointVariable;

                    auto formula = parseFormula(tokens, ++i, environment);
                    auto maxFixedPointFormula = std::make_shared<MaxFixedPoint>(fixedPointVariable, formula);
                    fixedPointVariable->setBoundingFormula(maxFixedPointFormula);
                    return std::make_shared<MaxFixedPoint>(fixedPointVariable, formula);
                    break;
                }
                case LEFT_DIAMOND_BRACKET: {
                    i++;
                    if (tokens[i].mType != ACTION_LABEL) {
                        throw std::runtime_error("Left opening of diamond not followed by action");
                    }
                    const std::string &actionLabel = tokens[i].mText;
                    i++;
                    if (tokens[i].mType != RIGHT_DIAMOND_BRACKET) {
                        throw std::runtime_error("Diamond is not closed by right brackets");
                    }
                    auto formula = parseFormula(tokens, ++i, environment);
                    return std::make_shared<Diamond>(actionLabel, formula);
                    break;
                }
                case LEFT_BOX_BRACKET: {
                    i++;
                    if (tokens[i].mType != ACTION_LABEL) {
                        throw std::runtime_error("Left opening of box not followed by action");
                    }
                    const std::string &actionLabel = tokens[i].mText;
                    i++;
                    if (tokens[i].mType != RIGHT_BOX_BRACKET) {
                        throw std::runtime_error("box is not closed by right bracket");
                    }
                    auto formula = parseFormula(tokens, ++i, environment);
                    return std::make_shared<Box>(actionLabel, formula);
                    break;
                }
                default:
                    throw std::runtime_error("Should not be reachable");
                    break;
            }
        }
        throw std::runtime_error("Should not be reachable");
    }




}


