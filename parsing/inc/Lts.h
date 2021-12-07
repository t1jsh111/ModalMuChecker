//
// Created by tijsh on 27-11-2021.
//

#ifndef MODALMUCHECKER_LTS_H
#define MODALMUCHECKER_LTS_H

#include <string>
#include <memory>
#include <map>
#include <set>


class Lts {

public:
    struct Transition;

    Lts(int initialState, int nrOfTransitions, int nrOfStates);

    void addTransition(int startState, std::string label, int endState);
    const std::set<std::shared_ptr<Transition>> & getTransitionsOfStartState(int startState) const;
    const std::set<std::shared_ptr<Transition>> & getTransitionsOfEndState(int endState) const;

    void printTransitionsOfStartState(int startState) const;
    void printTransitionsOfEndState(int endState) const;

    int getInitialState() const;

    int getNrOfTransitions() const;

    int getNrOfStates() const;

    const std::set<int> &getStates() const;

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

    std::set<int> states;


    std::map<int, std::set<std::shared_ptr<Transition>>> startStateToTransitions;
    std::map<int, std::set<std::shared_ptr<Transition>>> endStateToTransitions;

};


#endif //MODALMUCHECKER_LTS_H

