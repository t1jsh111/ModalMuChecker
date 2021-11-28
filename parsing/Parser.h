//
// Created by tijsh on 26-11-2021.
//

#ifndef MODALMUCHECKER_PARSER_H
#define MODALMUCHECKER_PARSER_H
#include <iostream>
#include <fstream>
#include "../DataRepresentations/Lts.h"

class Parser {
public:
    static Lts parseLts(const std::string& filePath);
    static void parseFormulaFile(const std::string& filePath);

private:
    static std::string getElementOfTuple(std::string tuple, int index);
};


#endif //MODALMUCHECKER_PARSER_H
