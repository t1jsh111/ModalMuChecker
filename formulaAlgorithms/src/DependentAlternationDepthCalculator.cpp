//
// Created by Tijs Hoeijmakers on 02/12/2021.
//

#include "DependentAlternationDepthCalculator.h"
#include "Formula.h"

int DependentAlternationDepthCalculator::computeDependentAlternatingNestingDepth(const Formula &formula) {
    const Formula::FormulaType& formulaType = formula.getFormulaType();
    switch (formulaType) {
        case Formula::TrueType:
        case Formula::FalseType:
        case Formula::FixedPointVariableType:
            return 0;
            break;
        case Formula::ConjunctionType: {
            const auto& conjunction = dynamic_cast<const Conjunction&>(formula);
            return std::max(computeDependentAlternatingNestingDepth(*conjunction.getMLeftFormula()),
                            computeDependentAlternatingNestingDepth(*conjunction.getMRightFormula()));
            break;
        }
        case Formula::DisjunctionType: {
            const auto& disjunction = dynamic_cast<const Disjunction&>(formula);
            return std::max(computeDependentAlternatingNestingDepth(*disjunction.getMLeftFormula()),
                            computeDependentAlternatingNestingDepth(*disjunction.getMRightFormula()));
            break;
        }
        case Formula::BoxType: {
            const auto &box = dynamic_cast<const Box &>(formula);
            return computeDependentAlternatingNestingDepth(*box.getMFormula());
            break;
        }
        case Formula::DiamondType: {
            const auto &diamond = dynamic_cast<const Diamond &>(formula);
            return computeDependentAlternatingNestingDepth(*diamond.getMFormula());
            break;
        }
        case Formula::MinFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MinFixedPoint &>(formula);
            int alternationDepth = std::max(1, computeDependentAlternatingNestingDepth(*fixedPoint.getMFormula()));
            auto maxFixedPoints = fixedPoint.getMFormula()->getMaxFixedPointFormulas();

            const auto& X = fixedPoint.getMFixedPointVariable();

            for(const auto& g : maxFixedPoints) {
                const auto& freeVariables = g.get().getFreeFixedPointVariables();
                bool found = false;
                for(const auto& freeVariable : freeVariables) {
                    if(freeVariable.get() == X) found = true;
                }
                if(found) {
                    alternationDepth = std::max(alternationDepth, 1 + computeDependentAlternatingNestingDepth(g));
                }

            }

            return alternationDepth;
        }
        case Formula::MaxFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MaxFixedPoint &>(formula);
            int alternationDepth = std::max(1, computeDependentAlternatingNestingDepth(*fixedPoint.getMFormula()));
            auto minFixedPoints = fixedPoint.getMFormula()->getMinFixedPointFormulas();

            const auto& X = fixedPoint.getMFixedPointVariable();

            for(const auto& g : minFixedPoints) {
                const auto& freeVariables = g.get().getFreeFixedPointVariables();
                bool found = false;
                for(const auto& freeVariable : freeVariables) {
                    if(freeVariable.get() == X) found = true;
                }

                if(found) {
                    alternationDepth = std::max(alternationDepth, 1 + computeDependentAlternatingNestingDepth(g));
                }

            }

            return alternationDepth;
        }
        default:
            throw std::runtime_error("This should not be reachable. Switch statement should be exhaustive...");
    }

    return 0;
}
