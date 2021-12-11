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
    }
}

void Lts::addTransition(int startState, std::string label, int endState) {
    std::shared_ptr<Transition> transition(new Transition{startState, label, endState});
    // If map does not contain startState as key, add a set for it
    if(startStateToTransitions.count(startState) <= 0) {
        startStateToTransitions.insert(std::pair<int,std::unordered_set<std::shared_ptr<Transition>>>(startState,{}));
    }
    // If map does not contain endState as key, add a set for it
    if(endStateToTransitions.count(endState) <= 0) {
        endStateToTransitions.insert(std::pair<int,std::unordered_set<std::shared_ptr<Transition>>>(endState,{}));
    }

    startStateToTransitions.at(startState).insert(transition);
    endStateToTransitions.at(endState).insert(transition);
}

const std::unordered_set<std::shared_ptr<Lts::Transition>> & Lts::getTransitionsOfSourceState(int sourceState) const {
    if(startStateToTransitions.count(sourceState) == 0) {
        startStateToTransitions[sourceState] = startStateToTransitions.at(sourceState);

    }
    return startStateToTransitions.at(sourceState);
}

const std::unordered_set<std::shared_ptr<Lts::Transition>> & Lts::getTransitionsOfTargetState(int targetState) const {
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
        transition->printTransition();
    }
}

void Lts::printTransitionsOfEndState(int endState) const {
    const auto& transitions = endStateToTransitions.at(endState);
    for(const auto& transition : transitions) {
        transition->printTransition();
    }
}

const std::unordered_set<int> & Lts::getStates() const {
    return states;
}


void Lts::Transition::printTransition() const {
    std::cout << "(" << this->startingState << ", " << this->label << ", "<< this->endState << ")";
}
