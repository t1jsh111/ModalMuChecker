//
// Created by Tijs Hoeijmakers on 02/12/2021.
//

#ifndef MODALMUCHECKER_NESTINGDEPTHCALCULATOR_H
#define MODALMUCHECKER_NESTINGDEPTHCALCULATOR_H

class Formula;

class NestingDepthCalculator {
public:
    static int computeNestingDepth(const Formula& formula);
};


#endif //MODALMUCHECKER_NESTINGDEPTHCALCULATOR_H
