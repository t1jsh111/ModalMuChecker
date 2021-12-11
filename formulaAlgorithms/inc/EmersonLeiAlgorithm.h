//
// Created by Milan Hutten on 11-12-2021.
//
#ifndef MODALMUCHECKER_EMERSONLEIALGORITHM_H
#define MODALMUCHECKER_EMERSONLEIALGORITHM_H

#include <set>
#include <unordered_map>
#include "Lts.h"
#include "Formula.h"


class EmersonLeiAlgorithm {
public:
    enum Context{empty, mu, nu};

    typedef std::unordered_map<FixedPointVariable, std::unordered_set<int>, FixedPointVariable::HashFunction> Mapping;

    static std::unordered_set<int> evaluate(const Formula & formula, const Lts & lts);
private:
    static std::unordered_set<int> evaluate(const Formula & formula, const Lts & lts, Mapping& A, Context context);

public:
    static int numberOfIterations;


};



#endif //MODALMUCHECKER_EMERSONLEIALGORITHM_H
