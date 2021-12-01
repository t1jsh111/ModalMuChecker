//
// Created by tijsh on 27-11-2021.
//

#ifndef MODALMUCHECKER_FORMULA_H
#define MODALMUCHECKER_FORMULA_H
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <iostream>

class Formula {
public:
    virtual void printFormula() = 0;
};

class True : public Formula{
    void printFormula() override {
        std::cout << "True";
    }
};

class False : public Formula {
    void printFormula() override {
        std::cout << "False";
    }
};

class FixedPointVariable : public Formula {
public:
    explicit FixedPointVariable(const char fixedPointVariable) : mFixedPointVariable(fixedPointVariable){}

    void printFormula() override {
        std::cout << mFixedPointVariable;
    }
private:
    const char mFixedPointVariable;
};

class Conjunction : public Formula {
public:
    Conjunction(std::shared_ptr<Formula> leftFormula, std::shared_ptr<Formula> rightFormula)
        : mLeftFormula(std::move(leftFormula)), mRightFormula(std::move(rightFormula)) {}

    void printFormula() override {
        std::cout << "(";
        mLeftFormula->printFormula();
        std::cout << " AND ";
        mRightFormula->printFormula();
        std::cout << ")";
    }
private:
    std::shared_ptr<Formula> mLeftFormula;
    std::shared_ptr<Formula> mRightFormula;
};

class Disjunction : public Formula {
public:
    Disjunction(std::shared_ptr<Formula> leftFormula, std::shared_ptr<Formula> rightFormula)
            : mLeftFormula(std::move(leftFormula)), mRightFormula(std::move(rightFormula)) {}

    void printFormula() override {
        std::cout << "(";
        mLeftFormula->printFormula();
        std::cout << " OR ";
        mRightFormula->printFormula();
        std::cout << ")";
    }
private:
    std::shared_ptr<Formula> mLeftFormula;
    std::shared_ptr<Formula> mRightFormula;
};

class Diamond : public Formula {
public:
    Diamond(std::string actionLabel, std::shared_ptr<Formula> formula)
        : mActionLabel(std::move(actionLabel)), mFormula(std::move(formula)) {};

    void printFormula() override {
        std::cout << "<" << mActionLabel << ">";
        mFormula->printFormula();
    }
private:
    const std::string mActionLabel;
    std::shared_ptr<Formula> mFormula;
};

class Box : public Formula {
public:
    Box(std::string actionLabel, std::shared_ptr<Formula> formula)
    : mActionLabel(std::move(actionLabel)), mFormula(std::move(formula)) {};

    void printFormula() override {
        std::cout << "[" << mActionLabel << "]";
        mFormula->printFormula();
    }
private:
    const std::string mActionLabel;
    std::shared_ptr<Formula> mFormula;
};

class FixedPoint : public Formula {
public:
    enum FixedPointType {mu, nu};



    FixedPoint(FixedPointType type, std::shared_ptr<FixedPointVariable> fixedPointVariable, std::shared_ptr<Formula> formula)
        : mType(type), mFixedPointVariable(std::move(fixedPointVariable)), mFormula(std::move(formula)) {}

    void printFormula() override {
        std::cout << tokenTypeToString[mType] << " ";
        mFixedPointVariable->printFormula();
        std::cout << ". ";
        mFormula->printFormula();
    }

private:
    const std::vector<std::string> tokenTypeToString = {"mu", "nu"};
    FixedPointType mType;
    std::shared_ptr<FixedPointVariable> mFixedPointVariable;
    std::shared_ptr<Formula> mFormula;
};


#endif //MODALMUCHECKER_FORMULA_H
