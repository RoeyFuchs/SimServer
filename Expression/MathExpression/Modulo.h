
#ifndef SIMSERVER_MODULO_H
#define SIMSERVER_MODULO_H

#include <cmath>

#include "../BinaryExpression.h"

class Modulo : protected BinaryExpression {
public:
    Modulo(Expression* left, Expression* right) : BinaryExpression(left, right) {}

    double Execute() override {
        return fmod(BinaryExpression::GetLeft()->Execute(), BinaryExpression::GetRight()->Execute());
    }

};

#endif //SIMSERVER_MODULO_H
