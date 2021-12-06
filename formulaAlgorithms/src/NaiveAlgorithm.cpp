//
// Created by Milan Hutten on 5-12-2021.
//

#include "NaiveAlgorithm.h"
#include "Formula.h"
#include "Lts.h"
#include <set>

std::set<int> NaiveAlgorithm::evaluate(const Formula & formula, const Lts & lts, std::pair<char, std::set<int>> * A) {
    const Formula::FormulaType& formulaType = formula.getFormulaType();
    switch (formulaType) {
        case Formula::TrueType: { // Return S
            std::set<int> S;
            for (int i = 0; i < lts.nrOfStates; i++) {
                S.emplace(i);
            }
            return S;
            break;
        }
        case Formula::FalseType: { // Return Empty set
            std::set<int> empty;
            return empty;
            break;
        }
        case Formula::FixedPointVariableType: {
            char var = dynamic_cast<const FixedPointVariable &>(formula).getFixedPointVariable();
            for (int i = 0; i < sizeof A; i++) {
                if (A[i].first == var) {
                    return A[i].second;
                    break;
                }
            }
            break;
        }
        case Formula::ConjunctionType: { // Return eval(g1) n eval(g2)
            const auto& conjunction = dynamic_cast<const Conjunction&>(formula);
            std::set<int> evalLeft = evaluate(*conjunction.getMLeftFormula(), lts, A);
            std::set<int> evalRight = evaluate(*conjunction.getMRightFormula(), lts, A);
            std::set<int> conjunct;
            for (int i : evalLeft) {
                if (evalRight.find(i) != evalRight.end()) {
                    conjunct.emplace(i);
                }
            }
            return conjunct;
            break;
        }
        /*case Formula::DisjunctionType: {
            const auto& disjunction = dynamic_cast<const Disjunction&>(formula);
            return std::max(computeAlternatingNestingDepth(*disjunction.getMLeftFormula()),
                            computeAlternatingNestingDepth(*disjunction.getMRightFormula()));
            break;
        }*/
        case Formula::BoxType: { // {s in S | All t in S: s -a-> t ==> t in eval(g)}
            const auto &box = dynamic_cast<const Box &>(formula);
            std::set<int> eval = evaluate(*box.getMFormula(), lts, A);
            std::string label = box.getMActionLabel();
            std::set<int> boxed;
            for (int i = 0; i < lts.nrOfStates; i++) {
                const std::set<std::shared_ptr<Lts::Transition>> transitions = lts.getTransitionsOfStartState(i);
                bool emplace = true;
                for (std::shared_ptr<Lts::Transition> t : transitions) {
                    if (t->label == label && eval.find(t->endState) == eval.end()) { // s -a-> t =/=> t in eval(g)
                        emplace = false;
                        break;
                    }
                }
                if (emplace) { // Only add s if All t in S: s -a-> t ==> t in eval(g)
                    boxed.emplace(i);
                }
            }
            return boxed;
            break;
        }
        /*case Formula::DiamondType: {
            const auto &diamond = dynamic_cast<const Diamond &>(formula);
            return computeAlternatingNestingDepth(*diamond.getMFormula());
            break;
        }*/
        /*case Formula::MinFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MinFixedPoint &>(formula);
            int alternationDepth = std::max(1, computeAlternatingNestingDepth(*fixedPoint.getMFormula()));
            auto maxFixedPoints = fixedPoint.getMFormula()->getMaxFixedPointFormulas();
            for(const auto& maxFixedPoint : maxFixedPoints) {
                alternationDepth = std::max(alternationDepth, 1 + computeAlternatingNestingDepth(maxFixedPoint));
            }

            return alternationDepth;
            break;
        }*/
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
            throw std::runtime_error("This should not be reachable. Switch statement not exhaustive...");
    }

    return 0;

}

