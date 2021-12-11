//
// Created by Milan Hutten on 5-12-2021.
//

#ifndef MODALMUCHECKER_NAIVEALGORITHM_H
#define MODALMUCHECKER_NAIVEALGORITHM_H

#include <set>
#include <unordered_map>
#include "Lts.h"
#include "Formula.h"


class NaiveAlgorithm {
public:
    typedef std::unordered_map<FixedPointVariable, std::unordered_set<int>, FixedPointVariable::HashFunction> Mapping;

    static std::unordered_set<int> evaluate(const Formula & formula, const Lts & lts);
private:
    static std::unordered_set<int> evaluate(const Formula & formula, const Lts & lts, Mapping& A);

public:
    static int numberOfIterations;
};

#endif //MODALMUCHECKER_NAIVEALGORITHM_H
