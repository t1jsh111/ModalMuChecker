//
// Created by Milan Hutten on 5-12-2021.
//

#include "NaiveAlgorithm.h"
#include "Formula.h"
#include "Lts.h"

int NaiveAlgorithm::numberOfIterations = 0;

std::unordered_set<int> NaiveAlgorithm::evaluate(const Formula & formula, const Lts & lts, Mapping& A) {
    const Formula::FormulaType& formulaType = formula.getFormulaType();
    switch (formulaType) {
        case Formula::TrueType: { // Return S
            return lts.getStates();
        }
        case Formula::FalseType: { // Return Empty set
            return {};
        }
        case Formula::FixedPointVariableType: { // Return A[i]
            const auto& fixedPointVariable = dynamic_cast<const FixedPointVariable &>(formula);

            bool variableIsKeyInA = (A.count(fixedPointVariable) != 0);
            if (variableIsKeyInA) {
                return A.at(fixedPointVariable);
            } else {
                throw std::runtime_error("No set has been assigned for " + std::string(1,fixedPointVariable.getFixedPointVariable()));
            }
            break;
        }
        case Formula::ConjunctionType: { // Return eval(g1) n eval(g2)
            const auto& conjunction = dynamic_cast<const Conjunction&>(formula);
            std::unordered_set<int> evalLeft = evaluate(*conjunction.getMLeftFormula(), lts, A);
            std::unordered_set<int> evalRight = evaluate(*conjunction.getMRightFormula(), lts, A);
            std::unordered_set<int> intersection;
            for (int i : evalLeft) {
                bool iExistsInRight = (evalRight.find(i) != evalRight.end());
                if (iExistsInRight) {
                    intersection.emplace(i);
                }
            }
            return intersection;
        }
        case Formula::DisjunctionType: { // Return eval(g1) u eval(g2)
            const auto& disjunction = dynamic_cast<const Disjunction&>(formula);
            std::unordered_set<int> evalLeft = evaluate(*disjunction.getMLeftFormula(), lts, A);
            std::unordered_set<int> evalRight = evaluate(*disjunction.getMRightFormula(), lts, A);
            std::unordered_set<int> setUnion = evalLeft;
            for (int i : evalRight) { // since setUnion we can simply add all elements. Set property will ensure no duplicates are there.
                setUnion.emplace(i);
            }
            return setUnion;
        }
        case Formula::BoxType: { // {s in S | All t in S: s -a-> t ==> t in eval(g)}
            const auto &box = dynamic_cast<const Box &>(formula);
            std::unordered_set<int> eval = evaluate(*box.getMFormula(), lts, A);
            std::string label = box.getMActionLabel();
            std::unordered_set<int> boxed;
            for (const auto& state : lts.getStates()) {
                const auto& transitions = lts.getTransitionsOfSourceState(state);
                bool emplace = true;
                for (const auto& transition : transitions) {
                    bool transitionWithLabelToStateNotInEval =
                            (transition.label == label && eval.find(transition.endState) == eval.end());

                    if (transitionWithLabelToStateNotInEval) { // s -a-> t =/=> t in eval(g)
                        // hence universal quantifier is violated
                        emplace = false;
                        break;
                    }
                }
                if (emplace) { // Only add s if All t in S: s -a-> t ==> t in eval(g)
                    boxed.emplace(state);
                }
            }
            return boxed;
        }
        case Formula::DiamondType: {
            const auto &diamond = dynamic_cast<const Diamond &>(formula);
            std::unordered_set<int> eval = evaluate(*diamond.getMFormula(), lts, A);
            std::string label = diamond.getMActionLabel();
            std::unordered_set<int> diamonded;
            for (const auto& state : lts.getStates()) {
                const auto& transitions = lts.getTransitionsOfSourceState(state);

                for (const auto& transition : transitions) {
                    bool transitionWithLabelToStateInEval = transition.label == label && eval.find(transition.endState) != eval.end();

                    if (transitionWithLabelToStateInEval) { // s -a-> t & t in eval(g)
                        // Hence existential quantifier holds
                        diamonded.emplace(state);
                        break;
                    }
                }
            }
            return diamonded;
        }
        case Formula::MinFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MinFixedPoint &>(formula);
            const auto& boundedVariable = fixedPoint.getMFixedPointVariable();

            A[boundedVariable] = {};
            std::unordered_set<int> Xold;
            do {
                numberOfIterations++;

                Xold = A[boundedVariable];
                A[boundedVariable] = evaluate(*fixedPoint.getMFormula(), lts, A);
            } while(Xold != A[boundedVariable]);

            return A[boundedVariable];
        }


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
            const auto& boundedVariable = fixedPoint.getMFixedPointVariable();

            A[boundedVariable] = lts.getStates();

            std::unordered_set<int> Xold;
            do {
                numberOfIterations++;

                Xold = A[boundedVariable];
                A[boundedVariable] = evaluate(*fixedPoint.getMFormula(), lts, A);
            } while(Xold != A[boundedVariable]);

            return A[boundedVariable];
        }
        default:
            throw std::runtime_error("This should not be reachable. Switch statement not exhaustive...");
    }

    std::unordered_set<int> empty;
    return empty;

}

std::unordered_set<int> NaiveAlgorithm::evaluate(const Formula &formula, const Lts &lts) {
    Mapping map = {};

    numberOfIterations = 0;

    return evaluate(formula, lts, map);
}

