//
// Created by tijsh on 27-11-2021.
//

#ifndef MODALMUCHECKER_FORMULA_H
#define MODALMUCHECKER_FORMULA_H
//#include <memory>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <set>
#include <unordered_set>

/*
 * Note that this is header only (implementation included in header)
 *
 * */
class MaxFixedPoint;
class MinFixedPoint;

class Formula {
public:
    enum FormulaType {TrueType, FalseType, FixedPointVariableType, ConjunctionType, DisjunctionType, BoxType,
            DiamondType, MaxFixedPointType, MinFixedPointType};
    explicit Formula(FormulaType formulaType) : mFormulatype(formulaType) {}
    FormulaType getFormulaType() const {return mFormulatype;}

    virtual void printFormula() const = 0;
    virtual std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const = 0;
    virtual std::vector<MinFixedPoint> getMinFixedPointFormulas() const = 0;

    const FormulaType mFormulatype;
};

class True : public Formula{
public:
    True() : Formula(TrueType){};

    void printFormula() const override {
        std::cout << "True";
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        return std::vector<MaxFixedPoint>();
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        return std::vector<MinFixedPoint>();
    }
};

class False : public Formula {
public:
    False() : Formula(FalseType) {}

    void printFormula() const override {
        std::cout << "False";
    }
    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        return std::vector<MaxFixedPoint>();
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        return std::vector<MinFixedPoint>();
    }
};

class FixedPointVariable : public Formula {
public:
    explicit FixedPointVariable(const char fixedPointVariable) : Formula(FixedPointVariableType), mFixedPointVariable(fixedPointVariable){}

    void printFormula() const override {
        std::cout << mFixedPointVariable;
    }
    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        return std::vector<MaxFixedPoint>();
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        return std::vector<MinFixedPoint>();
    }

private:
    const char mFixedPointVariable;
};

class Conjunction : public Formula {
public:
    Conjunction(std::shared_ptr<Formula> leftFormula, std::shared_ptr<Formula> rightFormula)
        : Formula(ConjunctionType), mLeftFormula(std::move(leftFormula)), mRightFormula(std::move(rightFormula)) {}

    void printFormula() const override {
        std::cout << "(";
        mLeftFormula->printFormula();
        std::cout << " AND ";
        mRightFormula->printFormula();
        std::cout << ")";
    }

    const std::shared_ptr<Formula> &getMLeftFormula() const {
        return mLeftFormula;
    }

    const std::shared_ptr<Formula> &getMRightFormula() const {
        return mRightFormula;
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        auto left = mLeftFormula->getMaxFixedPointFormulas();
        auto right = mRightFormula->getMaxFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        auto left = mLeftFormula->getMinFixedPointFormulas();
        auto right = mRightFormula->getMinFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }



private:
    std::shared_ptr<Formula> mLeftFormula;
    std::shared_ptr<Formula> mRightFormula;
};

class Disjunction : public Formula {
public:
    Disjunction(std::shared_ptr<Formula> leftFormula, std::shared_ptr<Formula> rightFormula)
            : Formula(DisjunctionType), mLeftFormula(std::move(leftFormula)), mRightFormula(std::move(rightFormula)) {}

    void printFormula() const override {
        std::cout << "(";
        mLeftFormula->printFormula();
        std::cout << " OR ";
        mRightFormula->printFormula();
        std::cout << ")";
    }

    const std::shared_ptr<Formula> &getMLeftFormula() const {
        return mLeftFormula;
    }

    const std::shared_ptr<Formula> &getMRightFormula() const {
        return mRightFormula;
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        auto left = mLeftFormula->getMaxFixedPointFormulas();
        auto right = mRightFormula->getMaxFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        auto left = mLeftFormula->getMinFixedPointFormulas();
        auto right = mRightFormula->getMinFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }



private:
    std::shared_ptr<Formula> mLeftFormula;
    std::shared_ptr<Formula> mRightFormula;
};

class Diamond : public Formula {
public:
    Diamond(std::string actionLabel, std::shared_ptr<Formula> formula)
        : Formula(DiamondType), mActionLabel(std::move(actionLabel)), mFormula(std::move(formula)) {};

    void printFormula() const override {
        std::cout << "<" << mActionLabel << ">";
        mFormula->printFormula();
    }

    const std::shared_ptr<Formula> &getMFormula() const {
        return mFormula;
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        return mFormula->getMaxFixedPointFormulas();
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        return mFormula->getMinFixedPointFormulas();
    }


private:
    const std::string mActionLabel;
    std::shared_ptr<Formula> mFormula;
};

class Box : public Formula {
public:
    Box(std::string actionLabel, std::shared_ptr<Formula> formula)
    : Formula(BoxType), mActionLabel(std::move(actionLabel)), mFormula(std::move(formula)) {};

    void printFormula() const override {
        std::cout << "[" << mActionLabel << "]";
        mFormula->printFormula();
    }

    const std::shared_ptr<Formula> &getMFormula() const {
        return mFormula;
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        return mFormula->getMaxFixedPointFormulas();
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        return mFormula->getMinFixedPointFormulas();
    }


private:
    const std::string mActionLabel;
    std::shared_ptr<Formula> mFormula;
};

class MaxFixedPoint : public Formula {
public:
    MaxFixedPoint(std::shared_ptr<FixedPointVariable> fixedPointVariable, std::shared_ptr<Formula> formula)
        : Formula(MaxFixedPointType), mFixedPointVariable(std::move(fixedPointVariable)), mFormula(std::move(formula)) {}

    void printFormula() const override {
        std::cout << "nu" << " ";
        mFixedPointVariable->printFormula();
        std::cout << ". ";
        mFormula->printFormula();
    }

    const std::shared_ptr<Formula> &getMFormula() const {
        return mFormula;
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{
        auto maxFixedPoints = mFormula->getMaxFixedPointFormulas();
        maxFixedPoints.push_back(*this);

        return maxFixedPoints;
    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        return mFormula->getMinFixedPointFormulas();
    }


private:
    std::shared_ptr<FixedPointVariable> mFixedPointVariable;
    std::shared_ptr<Formula> mFormula;
};

class MinFixedPoint : public Formula {
public:
    MinFixedPoint(std::shared_ptr<FixedPointVariable> fixedPointVariable, std::shared_ptr<Formula> formula)
    : Formula(MinFixedPointType), mFixedPointVariable(std::move(fixedPointVariable)), mFormula(std::move(formula)) {}


    void printFormula() const override {
        std::cout << "mu" << " ";
        mFixedPointVariable->printFormula();
        std::cout << ". ";
        mFormula->printFormula();
    }

    const std::shared_ptr<Formula> &getMFormula() const {
        return mFormula;
    }

    std::vector<MaxFixedPoint> getMaxFixedPointFormulas() const override{

        return mFormula->getMaxFixedPointFormulas();

    }

    std::vector<MinFixedPoint> getMinFixedPointFormulas() const override{
        auto minFixedPoints = mFormula->getMinFixedPointFormulas();
        minFixedPoints.push_back(*this);

        return minFixedPoints;
    }


private:
    std::shared_ptr<FixedPointVariable> mFixedPointVariable;
    std::shared_ptr<Formula> mFormula;
};


#endif //MODALMUCHECKER_FORMULA_H
