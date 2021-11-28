//
// Created by tijsh on 26-11-2021.
//

#include "Parser.h"

#include <iostream>

//LtsParser::LtsParser(const std::string &filePath) : autFile(filePath){
//    if(!autFile.is_open()) {
//        std::cout << "Error: could not open the provided file...";
//    }
//}

Lts Parser::parseLts(const std::string &filePath) {
    std::ifstream autFile(filePath);

    if(!autFile.is_open()) {
        std::cout << "Error: could not open the provided file...";
    }


    std::string currentWord;
    autFile >> currentWord;
    // The first word of a .aut file should always contain des
    if(currentWord != "des") {
        return Lts(0,0,0);
    }


    autFile >> currentWord; // currentWord gets assigned the tuple after 'des'
    int firstState = std::stoi(getElementOfTuple(currentWord, 0));
    int nrOfTransitions = std::stoi(getElementOfTuple(currentWord, 1));
    int nrOfStates = std::stoi(getElementOfTuple(currentWord, 2));

    Lts lts(firstState, nrOfTransitions, nrOfStates);


    // Add transitions to the lts
    while(autFile >> currentWord) {

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

    if(tuple.at(0) != '(' || tuple.at(tuple.length()-1) != ')') {
        std::cout << "This is not a tuple!!";
        return "";
    }

    for(int i = 1; i < tuple.length() - 1; i++) {
        if(tuple.at(i) == ',') {
            currentIndex++;
            continue;
        }

        if(currentIndex == index) {
            returnString.push_back(tuple.at(i));
        }

    }

    if(currentIndex < index) {
        std::cout << "Index out of tuple boundary";
        return "";
    }

    return returnString;
}

void Parser::parseFormulaFile(const std::string &filePath) {
    std::ifstream formulaFile(filePath);

    if(!formulaFile.is_open()) {
        std::cout << "Error: could not open the provided file...";
    }

    std::string currentWord;
    while(formulaFile >> currentWord) {
        std::cout << currentWord << std::endl;
    }

}



