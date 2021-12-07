//
// Created by Tijs Hoeijmakers on 02/12/2021.
//

#ifndef MODALMUCHECKER_DEPENDENTALTERNATIONDEPTHCALCULATOR_H
#define MODALMUCHECKER_DEPENDENTALTERNATIONDEPTHCALCULATOR_H

class Formula;

class DependentAlternationDepthCalculator {
public:
    static int computeDependentAlternatingNestingDepth(const Formula& formula);

};


#endif //MODALMUCHECKER_DEPENDENTALTERNATIONDEPTHCALCULATOR_H
