#ifndef SIMSERVER_MINUS_H
#define SIMSERVER_MINUS_H


#include "../BinaryExpression.h"

class Minus : public BinaryExpression {
public:
    Minus(Expression* left, Expression* right) : BinaryExpression(left, right) {}

    double Execute() override {
        return BinaryExpression::GetLeft()->Execute() - BinaryExpression::GetRight()->Execute();
    }

};

#endif //SIMSERVER_MINUS_H
