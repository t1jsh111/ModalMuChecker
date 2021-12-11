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


class Lts {

public:
    struct Transition;

    Lts(int initialState, int nrOfTransitions, int nrOfStates);

    void addTransition(int startState, std::string label, int endState);
    const std::unordered_set<std::shared_ptr<Transition>> & getTransitionsOfSourceState(int sourceState) const;
    const std::unordered_set<std::shared_ptr<Transition>> & getTransitionsOfTargetState(int targetState) const;

    void printTransitionsOfStartState(int startState) const;
    void printTransitionsOfEndState(int endState) const;

    int getInitialState() const;

    int getNrOfTransitions() const;

    int getNrOfStates() const;

    const std::unordered_set<int> & getStates() const;

    struct Transition {
        int startingState;
        std::string label;
        int endState;

        void printTransition() const;
    };

public:
    int initialState;
    int nrOfTransitions;
    int nrOfStates;

    std::unordered_set<int> states;


    std::map<int, std::unordered_set<std::shared_ptr<Transition>>> startStateToTransitions;
    std::map<int, std::unordered_set<std::shared_ptr<Transition>>> endStateToTransitions;

};


#endif //MODALMUCHECKER_LTS_H

