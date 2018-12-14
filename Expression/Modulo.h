
#ifndef SIMSERVER_MODULO_H
#define SIMSERVER_MODULO_H

#include <cmath>

#include "BinaryExpression.h"

class Modulo : protected BinaryExpression {
public:
    Modulo(Expression* left, Expression* right) : BinaryExpression(left, right) {}

    double execute() override {
        return fmod(BinaryExpression::GetLeft()->execute(), BinaryExpression::GetRight()->execute());
    }

};

#endif //SIMSERVER_MODULO_H
