//
// Created by tijsh on 27-11-2021.
//

#include "../inc/Lts.h"
#include <iostream>

Lts::Lts(int initialState, int nrOfTransitions, int nrOfStates) :
    initialState(initialState), nrOfTransitions(nrOfTransitions), nrOfStates(nrOfStates)
{

}

void Lts::addTransition(int startState, std::string label, int endState) {
    std::shared_ptr<Transition> transition(new Transition{startState, label, endState});
    // If map does not contain startState as key, add a set for it
    if(startStateToTransitions.count(startState) <= 0) {
        startStateToTransitions.insert(std::pair<int,std::set<std::shared_ptr<Transition>>>(startState,{}));
    }
    // If map does not contain endState as key, add a set for it
    if(endStateToTransitions.count(endState) <= 0) {
        endStateToTransitions.insert(std::pair<int,std::set<std::shared_ptr<Transition>>>(endState,{}));
    }

    startStateToTransitions.at(startState).insert(transition);
    endStateToTransitions.at(endState).insert(transition);
}

const std::set<std::shared_ptr<Lts::Transition>> & Lts::getTransitionsOfStartState(int startState) const {
    return startStateToTransitions.at(startState);
}

const std::set<std::shared_ptr<Lts::Transition>> & Lts::getTransitionsOfEndState(int endState) const {
    return endStateToTransitions.at(endState);
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


void Lts::Transition::printTransition() const {
    std::cout << "(" << this->startingState << "," << this->endState << ")";
}
