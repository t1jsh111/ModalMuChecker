//
// Created by Milan Hutten on 5-12-2021.
//

#include "NaiveAlgorithm.h"
#include "Formula.h"
#include "Lts.h"
#include <set>

std::set<int> NaiveAlgorithm::evaluate(const Formula & formula, const Lts & lts, std::unordered_map<FixedPointVariable, std::set<int>> A) {
    const Formula::FormulaType& formulaType = formula.getFormulaType();
    switch (formulaType) {
        case Formula::TrueType: { // Return S
            return lts.getStates();
        }
        case Formula::FalseType: { // Return Empty set
            std::set<int> empty;
            return empty;
        }
        case Formula::FixedPointVariableType: { // Return A[i]
            const auto& fixedPointVariable = dynamic_cast<const FixedPointVariable &>(formula);
            if (A.count(fixedPointVariable) != 0) {
                return A.at(fixedPointVariable);
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
        }
        case Formula::DisjunctionType: { // Return eval(g1) u eval(g2)
            const auto& disjunction = dynamic_cast<const Disjunction&>(formula);
            std::set<int> evalLeft = evaluate(*disjunction.getMLeftFormula(), lts, A);
            std::set<int> evalRight = evaluate(*disjunction.getMRightFormula(), lts, A);
            std::set<int> disjunct = evalLeft;
            for (int i : evalRight) {
                //if (disjunct.find(i) == disjunct.end()) {
                    disjunct.emplace(i);
                //}
            }
            return disjunct;
        }
        case Formula::BoxType: { // {s in S | All t in S: s -a-> t ==> t in eval(g)}
            const auto &box = dynamic_cast<const Box &>(formula);
            std::set<int> eval = evaluate(*box.getMFormula(), lts, A);
            std::string label = '"' + box.getMActionLabel() + '"';
            std::set<int> boxed;
            for (int i = 0; i < lts.nrOfStates; i++) {
                const std::set<std::shared_ptr<Lts::Transition>> transitions = lts.getTransitionsOfSourceState(i);
                bool emplace = true;
                for (std::shared_ptr<Lts::Transition> t : transitions) {
                    if (t->label.compare(label) == 0 && eval.find(t->endState) == eval.end()) { // s -a-> t =/=> t in eval(g)
                        emplace = false;
                        break;
                    }
                }
                if (emplace) { // Only add s if All t in S: s -a-> t ==> t in eval(g)
                    boxed.emplace(i);
                }
            }
            return boxed;
        }
        case Formula::DiamondType: {
            const auto &diamond = dynamic_cast<const Diamond &>(formula);
            std::set<int> eval = evaluate(*diamond.getMFormula(), lts, A);
            std::string label = '"' + diamond.getMActionLabel() + '"';
            std::set<int> diamonded;
            for (int i = 0; i < lts.nrOfStates; i++) {
                const std::set<std::shared_ptr<Lts::Transition>> transitions = lts.getTransitionsOfSourceState(i);
                for (std::shared_ptr<Lts::Transition> t : transitions) {
                    if (t->label.compare(label) == 0 && eval.find(t->endState) != eval.end()) { // s -a-> t & t in eval(g)
                        diamonded.emplace(i);
                        break;
                    }
                }
            }
            return diamonded;
        }
        case Formula::MinFixedPointType: {
            const auto &fixedPoint = dynamic_cast<const MinFixedPoint &>(formula);
            const auto& boundedVariable = fixedPoint.getMFixedPointVariable();

            A[boundedVariable] = std::set<int>();

            std::set<int> X = lts.getStates();
            while (X != A[boundedVariable]) {
                X = A[boundedVariable]; // X' := A[i]
                A[boundedVariable] = evaluate(*fixedPoint.getMFormula(), lts, A); // A[i] := eval(g)
            }

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

            // A[i] := S
            std::set<int> S;
            const auto& allStates = lts.getStates();
            A[boundedVariable] = allStates;

            std::set<int> X;
            while (X != A[boundedVariable]) {
                X = A[boundedVariable]; // X' := A[i]
                A[boundedVariable] = evaluate(*fixedPoint.getMFormula(), lts, A); // A[i] := eval(g)
            }

            return A[boundedVariable];
        }
        default:
            throw std::runtime_error("This should not be reachable. Switch statement not exhaustive...");
    }

    std::set<int> empty;
    return empty;

}

