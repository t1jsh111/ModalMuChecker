//
// Created by tijsh on 27-11-2021.
//

#ifndef MODALMUCHECKER_FORMULA_H
#define MODALMUCHECKER_FORMULA_H


class Formula {

};

class True : public Formula{

};

class False : public Formula {

};

class FixedPointVariable : public Formula {

};

class Conjunction : public Formula {

};

class Disjunction : public Formula {

};

class Diamond : public Formula {

};

class Box : public Formula {

};

class FixedPoint : public Formula {
public:
    enum FixedPointType {mu, nu};

    explicit FixedPoint(FixedPointType type);

private:
    FixedPointType type;
};


#endif //MODALMUCHECKER_FORMULA_H
