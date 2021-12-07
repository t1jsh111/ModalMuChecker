//
// Created by Tijs Hoeijmakers on 02/12/2021.
//

#include "AlternatingNestingDepthCalculator.h"
#include "Formula.h"

int AlternatingNestingDepthCalculator::computeAlternatingNestingDepth(const Formula &formula) {
    const Formula::FormulaType& formulaType = formula.getFormulaType();
    switch (formulaType) {
        case Formula::TrueType:
        case Formula::FalseType:
        case Formula::FixedPointVariableType:
            return 0;
            break;
        case Formula::ConjunctionType: {
            const auto& conjunction = dynamic_cast<const Conjunction&>(formula);
            return std::max(computeAlternatingNestingDepth(*conjunction.getMLeftFormula()),
                            computeAlternatingNestingDepth(*conjunction.getMRightFormula()));
            break;
        }
        case Formula::DisjunctionType: {
            const auto& disjunction = dynamic_cast<const Disjunction&>(formula);
            return std::max(computeAlternatingNestingDepth(*disjunction.getMLeftFormula()),
                            computeAlternatingNestingDepth(*disjunction.getMRightFormula()));
            break;
        }
        case Formula::BoxType: {
            const auto &box = dynamic_cast<const Box &>(formula);
            return computeAlternatingNestingDepth(*box.getMFormula());
            break;
        }
        case Formula::DiamondType: {
            const auto &diamond = dynamic_cast<const Diamond &>(formula);
            return computeAlternatingNestingDepth(*diamond.getMFormula());
            break;
        }
        case Formula::MinFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MinFixedPoint &>(formula);
            int alternationDepth = std::max(1, computeAlternatingNestingDepth(*fixedPoint.getMFormula()));
            auto maxFixedPoints = fixedPoint.getMFormula()->getMaxFixedPointFormulas();
            for(const auto& maxFixedPoint : maxFixedPoints) {
                alternationDepth = std::max(alternationDepth, 1 + computeAlternatingNestingDepth(maxFixedPoint));
            }

            return alternationDepth;
            break;
        }
        case Formula::MaxFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MaxFixedPoint &>(formula);
            int alternationDepth = std::max(1, computeAlternatingNestingDepth(*fixedPoint.getMFormula()));
            auto minFixedPoints = fixedPoint.getMFormula()->getMinFixedPointFormulas();
            for(const auto& minFixedPoint : minFixedPoints) {
                alternationDepth = std::max(alternationDepth, 1 + computeAlternatingNestingDepth(minFixedPoint));
            }

            return alternationDepth;
        }
        default:
            throw std::runtime_error("This should not be reachable. Switch statement should be exhaustive...");
    }

    return 0;

}
