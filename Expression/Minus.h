#ifndef SIMSERVER_MINUS_H
#define SIMSERVER_MINUS_H


#include "BinaryExpression.h"

class Minus : protected BinaryExpression {
public:
    Minus(Expression* left, Expression* right) : BinaryExpression(left, right) {}

    double execute() override {
        return BinaryExpression::GetLeft()->execute() - BinaryExpression::GetRight()->execute();
    }

};

#endif //SIMSERVER_MINUS_H
