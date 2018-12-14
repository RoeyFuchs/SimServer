#ifndef SIMSERVER_MULT_H
#define SIMSERVER_MULT_H

#include "../BinaryExpression.h"

class Mult : public BinaryExpression{
public:
    Mult(Expression* left, Expression* right) : BinaryExpression(left, right) {}

    double Execute() override {
        return BinaryExpression::GetLeft()->Execute() * BinaryExpression::GetRight()->Execute();
    }

};

#endif //SIMSERVER_MULT_H