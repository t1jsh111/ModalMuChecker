//
// Created by Tijs Hoeijmakers on 02/12/2021.
//

#include "NestingDepthCalculator.h"
#include "Formula.h"

int NestingDepthCalculator::computeNestingDepth(const Formula& formula) {

    const Formula::FormulaType& formulaType = formula.getFormulaType();
    switch (formulaType) {
        case Formula::TrueType:
        case Formula::FalseType:
        case Formula::FixedPointVariableType:
            return 0;
            break;
        case Formula::ConjunctionType: {
            const auto& conjunction = dynamic_cast<const Conjunction&>(formula);
            return std::max(computeNestingDepth(*conjunction.getMLeftFormula()),
                            computeNestingDepth(*conjunction.getMRightFormula()));
            break;
        }
        case Formula::DisjunctionType: {
            const auto& disjunction = dynamic_cast<const Disjunction&>(formula);
            return std::max(computeNestingDepth(*disjunction.getMLeftFormula()),
                            computeNestingDepth(*disjunction.getMRightFormula()));
            break;
        }
        case Formula::BoxType: {
            const auto &box = dynamic_cast<const Box &>(formula);
            return computeNestingDepth(*box.getMFormula());
            break;
        }
        case Formula::DiamondType: {
            const auto &diamond = dynamic_cast<const Diamond &>(formula);
            return computeNestingDepth(*diamond.getMFormula());
            break;
        }
        case Formula::MinFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MinFixedPoint &>(formula);
            return computeNestingDepth(*fixedPoint.getMFormula()) + 1;
            break;
        }
        case Formula::MaxFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MaxFixedPoint &>(formula);
            return computeNestingDepth(*fixedPoint.getMFormula()) + 1;
            break;
        }
        default:
            throw std::runtime_error("This should not be reachable. Switch statement should be exhaustive...");
    }

    return 0;
}
