//
// Created by tijsh on 27-11-2021.
//

#ifndef MODALMUCHECKER_LTS_H
#define MODALMUCHECKER_LTS_H

#include <string>

#include <memory>
#include <map>
#include <set>
#include <unordered_set>
#include <string_view>


class Lts {

public:
    struct Transition {
        int startingState;
        std::string label;
        int endState;

        void printTransition() const;

        bool operator==(const Transition& rhs) const {
            return startingState == rhs.startingState && label == rhs.label && endState == rhs.endState;
        }

        struct HashFunction {
            std::size_t operator() (const Transition &transition) const
            {
                std::size_t h1 = std::hash<int>()(transition.startingState);
                std::size_t h2 = std::hash<std::string>()(transition.label);
                std::size_t h3 = std::hash<int>()(transition.endState);

                return h1 ^ h2 ^ h3;
            }
        };

    };

    Lts(int initialState, int nrOfTransitions, int nrOfStates);

    void addTransition(int startState, std::string label, int endState);
    const std::unordered_set<Transition, Transition::HashFunction> & getTransitionsOfSourceState(int sourceState) const;
    const std::unordered_set<Transition, Transition::HashFunction> & getTransitionsOfTargetState(int targetState) const;

    void printTransitionsOfStartState(int startState) const;
    void printTransitionsOfEndState(int endState) const;

    int getInitialState() const;

    int getNrOfTransitions() const;

    int getNrOfStates() const;

    const std::unordered_set<int> & getStates() const;



public:
    int initialState;
    int nrOfTransitions;
    int nrOfStates;

    std::unordered_set<int> states;


    std::map<int, std::unordered_set<Transition,Transition::HashFunction>> startStateToTransitions;
    std::map<int, std::unordered_set<Transition,Transition::HashFunction>> endStateToTransitions;

};


#endif //MODALMUCHECKER_LTS_H

