#ifndef SIMSERVER_MULT_H
#define SIMSERVER_MULT_H

#include "BinaryExpression.h"

class Mult : protected BinaryExpression{
public:
    Mult(Expression* left, Expression* right) : BinaryExpression(left, right) {}

    double execute() override {
        return BinaryExpression::GetLeft()->execute() * BinaryExpression::GetRight()->execute();
    }

};

#endif //SIMSERVER_MULT_H
