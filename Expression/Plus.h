#ifndef SIMSERVER_PLUS_H
#define SIMSERVER_PLUS_H

#include "BinaryExpression.h"

class Plus : protected BinaryExpression {
public:
    Plus(Expression* left, Expression* right) : BinaryExpression(left, right) {}

     double execute() override {
        return BinaryExpression::GetLeft()->execute() + BinaryExpression::GetRight()->execute();
    }

};

#endif //SIMSERVER_PLUS_H
