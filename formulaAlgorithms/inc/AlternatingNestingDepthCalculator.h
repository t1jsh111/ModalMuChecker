//
// Created by Tijs Hoeijmakers on 02/12/2021.
//

#ifndef MODALMUCHECKER_ALTERNATINGNESTINGDEPTHCALCULATOR_H
#define MODALMUCHECKER_ALTERNATINGNESTINGDEPTHCALCULATOR_H

class Formula;

class AlternatingNestingDepthCalculator {
public:
    static int computeAlternatingNestingDepth(const Formula& formula);
};


#endif //MODALMUCHECKER_ALTERNATINGNESTINGDEPTHCALCULATOR_H
