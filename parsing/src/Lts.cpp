//
// Created by tijsh on 27-11-2021.
//

#include "Lts.h"
#include <iostream>

Lts::Lts(int initialState, int nrOfTransitions, int nrOfStates) :
    initialState(initialState), nrOfTransitions(nrOfTransitions), nrOfStates(nrOfStates)
{
    for(int i = 0; i < nrOfStates; i++) {
        this->states.insert(i);
        startStateToTransitions[i] = {};
        endStateToTransitions[i] = {};
    }
}

void Lts::addTransition(int startState, std::string label, int endState) {
    startStateToTransitions.at(startState).insert(Transition{startState, label, endState});
    endStateToTransitions.at(endState).insert(Transition{startState, label, endState});
}

const std::unordered_set<Lts::Transition, Lts::Transition::HashFunction> & Lts::getTransitionsOfSourceState(int sourceState) const {

    return startStateToTransitions.at(sourceState);
}

const std::unordered_set<Lts::Transition, Lts::Transition::HashFunction> & Lts::getTransitionsOfTargetState(int targetState) const {
    return endStateToTransitions.at(targetState);
}

int Lts::getInitialState() const {
    return initialState;
}

int Lts::getNrOfTransitions() const {
    return nrOfTransitions;
}

int Lts::getNrOfStates() const {
    return nrOfStates;
}

void Lts::printTransitionsOfStartState(int startState) const {
    const auto& transitions = startStateToTransitions.at(startState);
    for(const auto& transition : transitions) {
        transition.printTransition();
    }
}

void Lts::printTransitionsOfEndState(int endState) const {
    const auto& transitions = endStateToTransitions.at(endState);
    for(const auto& transition : transitions) {
        transition.printTransition();
    }
}

const std::unordered_set<int> & Lts::getStates() const {
    return states;
}


void Lts::Transition::printTransition() const {
    std::cout << "(" << this->startingState << ", " << this->label << ", "<< this->endState << ")";
}
