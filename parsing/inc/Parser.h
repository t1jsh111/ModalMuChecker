//
// Created by tijsh on 26-11-2021.
//

#ifndef MODALMUCHECKER_PARSER_H
#define MODALMUCHECKER_PARSER_H
#include <iostream>
#include <fstream>
#include "Tokenizer.h"
#include "Lts.h"
#include "Formula.h"

namespace parser_space {
    class Parser {
    public:
        static Lts parseLts(const std::string &filePath);

        static std::shared_ptr<Formula> parseFormulaFile(const std::string &filePath);
        static std::shared_ptr<Formula> parseFormula(const std::string& formula);

    private:
        static std::string getElementOfTuple(std::string tuple, int index);
        static std::shared_ptr<Formula> parseFormula(std::vector<Token>& tokens);
        static std::shared_ptr<Formula> parseFormula(std::vector<Token>& tokens, size_t& startPosition);
    };
}

#endif //MODALMUCHECKER_PARSER_H
