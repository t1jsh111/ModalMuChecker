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
#include <memory>
#include <list>

/*
 * Note that this is header only (implementation included in header)
 *
 * */
class MaxFixedPoint;
class MinFixedPoint;
class FixedPointVariable;
class FixedPoint;
struct FixedPointVariableHashFunction;


class Formula {
public:
    enum FormulaType {TrueType, FalseType, FixedPointVariableType, ConjunctionType, DisjunctionType, BoxType,
            DiamondType, MaxFixedPointType, MinFixedPointType};
    explicit Formula(FormulaType formulaType) : mFormulatype(formulaType) {}
    FormulaType getFormulaType() const {return mFormulatype;}

    virtual void printFormula() const = 0;
    virtual std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const = 0;
    virtual std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const = 0;
    virtual std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const = 0;
    virtual std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const = 0;

    const FormulaType mFormulatype;
};


class FixedPointVariable : public Formula {
    friend FixedPointVariableHashFunction;
public:
    explicit FixedPointVariable(const char fixedPointVariable) : Formula(FixedPointVariableType), mFixedPointVariable(fixedPointVariable){}

    void printFormula() const override {
        std::cout << mFixedPointVariable;
    }

    char getFixedPointVariable() const {
        return mFixedPointVariable;
    }

    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        return std::vector<std::reference_wrapper<const MaxFixedPoint>>();
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        return std::vector<std::reference_wrapper<const MinFixedPoint>>();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return {*this};
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        return {*this};
    }

    bool operator==(const FixedPointVariable& rhs) const {
        return mFixedPointVariable == rhs.mFixedPointVariable && boundingFormula == rhs.boundingFormula;
    }

    void setBoundingFormula(std::shared_ptr<FixedPoint> formula) {
        boundingFormula = formula;
    }


private:
    const char mFixedPointVariable;
    std::shared_ptr<FixedPoint> boundingFormula;
};



struct FixedPointVariableHashFunction{
    size_t operator()(const FixedPointVariable& a) const {
        size_t xHash = std::hash<char>()(a.mFixedPointVariable);
        return xHash;
    }
};



class True : public Formula{
public:
    True() : Formula(TrueType){};

    void printFormula() const override {
        std::cout << "True";
    }
    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        return std::vector<std::reference_wrapper<const MaxFixedPoint>>();
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        return std::vector<std::reference_wrapper<const MinFixedPoint>>();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return std::list<std::reference_wrapper<const FixedPointVariable>>();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
            getFreeFixedPointVariables() const override {
        return std::list<std::reference_wrapper<const FixedPointVariable>>();
    }
};

class False : public Formula {
public:
    False() : Formula(FalseType) {}

    void printFormula() const override {
        std::cout << "False";
    }



    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        return std::vector<std::reference_wrapper<const MaxFixedPoint>>();
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        return std::vector<std::reference_wrapper<const MinFixedPoint>>();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return std::list<std::reference_wrapper<const FixedPointVariable>>();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        return std::list<std::reference_wrapper<const FixedPointVariable>>();
    }
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

    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        auto left = mLeftFormula->getMaxFixedPointFormulas();
        auto right = mRightFormula->getMaxFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        auto left = mLeftFormula->getMinFixedPointFormulas();
        auto right = mRightFormula->getMinFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        auto left = mLeftFormula->getFixedPointVariables();
        auto right = mRightFormula->getFixedPointVariables();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        auto left = mLeftFormula->getFreeFixedPointVariables();
        auto right = mRightFormula->getFreeFixedPointVariables();
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

    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        auto left = mLeftFormula->getMaxFixedPointFormulas();
        auto right = mRightFormula->getMaxFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        auto left = mLeftFormula->getMinFixedPointFormulas();
        auto right = mRightFormula->getMinFixedPointFormulas();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        auto left = mLeftFormula->getFixedPointVariables();
        auto right = mRightFormula->getFixedPointVariables();
        std::copy(right.begin(), right.end(), std::back_inserter(left));

        return left;
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        auto left = mLeftFormula->getFreeFixedPointVariables();
        auto right = mRightFormula->getFreeFixedPointVariables();
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


    const std::string &getMActionLabel() const {
        return mActionLabel;
    }


    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        return mFormula->getMaxFixedPointFormulas();
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        return mFormula->getMinFixedPointFormulas();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return mFormula->getFixedPointVariables();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        return mFormula->getFreeFixedPointVariables();
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


    const std::string &getMActionLabel() const {
        return mActionLabel;
    }


    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{
        return mFormula->getMaxFixedPointFormulas();
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        return mFormula->getMinFixedPointFormulas();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return mFormula->getFixedPointVariables();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        return mFormula->getFreeFixedPointVariables();
    }


private:
    const std::string mActionLabel;
    std::shared_ptr<Formula> mFormula;
};

class FixedPoint {
public:
    enum FixedPointFormulaType {MaxFixedPointFormula, MinFixedPointFormula};
    explicit FixedPoint(FixedPointFormulaType formulaType) : mFormulatype(formulaType) {}
private:
    const FixedPointFormulaType mFormulatype;
};

class MaxFixedPoint : public Formula, public FixedPoint {
public:
    MaxFixedPoint(std::shared_ptr<FixedPointVariable> fixedPointVariable, std::shared_ptr<Formula> formula)
        : Formula(MaxFixedPointType), FixedPoint(FixedPointFormulaType::MaxFixedPointFormula),
        mFixedPointVariable(std::move(fixedPointVariable)), mFormula(std::move(formula)) {}

    void printFormula() const override {
        std::cout << "nu" << " ";
        mFixedPointVariable->printFormula();
        std::cout << ". ";
        mFormula->printFormula();
    }

    const std::shared_ptr<Formula> &getMFormula() const {
        return mFormula;
    }


    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{

        auto maxFixedPoints = mFormula->getMaxFixedPointFormulas();
        maxFixedPoints.emplace_back(*this);

        return maxFixedPoints;
    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        return mFormula->getMinFixedPointFormulas();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return mFormula->getFixedPointVariables();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        auto variables = mFormula->getFreeFixedPointVariables();
        for(auto it = variables.begin(); it != variables.end(); it++) {
            if(*mFixedPointVariable == *it) {
                variables.erase(it);
            }
        }
        return variables;
    }

    const FixedPointVariable& getMFixedPointVariable() const {
        return *mFixedPointVariable;
    }

private:
    std::shared_ptr<FixedPointVariable> mFixedPointVariable;


private:
    std::shared_ptr<Formula> mFormula;
};

class MinFixedPoint : public Formula, public FixedPoint {
public:
    MinFixedPoint(std::shared_ptr<FixedPointVariable> fixedPointVariable, std::shared_ptr<Formula> formula)
    : Formula(MinFixedPointType), FixedPoint(FixedPointFormulaType::MinFixedPointFormula),
    mFixedPointVariable(std::move(fixedPointVariable)), mFormula(std::move(formula)) {}


    void printFormula() const override {
        std::cout << "mu" << " ";
        mFixedPointVariable->printFormula();
        std::cout << ". ";
        mFormula->printFormula();
    }

    const std::shared_ptr<Formula> &getMFormula() const {
        return mFormula;
    }

    std::vector<std::reference_wrapper<const MaxFixedPoint>> getMaxFixedPointFormulas() const override{

        return mFormula->getMaxFixedPointFormulas();

    }

    std::vector<std::reference_wrapper<const MinFixedPoint>> getMinFixedPointFormulas() const override{
        auto minFixedPoints = mFormula->getMinFixedPointFormulas();
        minFixedPoints.emplace_back(*this);

        return minFixedPoints;
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFixedPointVariables() const override {
        return mFormula->getFixedPointVariables();
    }

    std::list<std::reference_wrapper<const FixedPointVariable>>
    getFreeFixedPointVariables() const override {
        auto variables = mFormula->getFreeFixedPointVariables();
        for(auto it = variables.begin(); it != variables.end(); it++) {
            if(*mFixedPointVariable == *it) {
                variables.erase(it);
            }
        }
        return variables;
    }

    const FixedPointVariable& getMFixedPointVariable() const {
        return *mFixedPointVariable;
    }


private:
    std::shared_ptr<FixedPointVariable> mFixedPointVariable;
    std::shared_ptr<Formula> mFormula;
};


#endif //MODALMUCHECKER_FORMULA_H
