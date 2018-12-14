#ifndef SIMSERVER_PLUS_H
#define SIMSERVER_PLUS_H

#include "BinaryExpression.h"

class Plus : protected BinaryExpression {
public:
    Plus(Expression* left, Expression* right) : BinaryExpression(left, right) {}

     double Execute() override {
        return BinaryExpression::GetLeft()->Execute() + BinaryExpression::GetRight()->Execute();
    }

};

#endif //SIMSERVER_PLUS_H
