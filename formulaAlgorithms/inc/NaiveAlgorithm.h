//
// Created by Milan Hutten on 5-12-2021.
//

#ifndef MODALMUCHECKER_NAIVEALGORITHM_H
#define MODALMUCHECKER_NAIVEALGORITHM_H

#include <set>
#include <unordered_map>
#include "Lts.h"

class Formula;

class NaiveAlgorithm {
public:
    static std::set<int> evaluate(const Formula & formula, const Lts & lts, std::unordered_map<FixedPointVariable, std::set<int>> A);
};

#endif //MODALMUCHECKER_NAIVEALGORITHM_H
