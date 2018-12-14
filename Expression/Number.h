#ifndef SIMSERVER_NUMBER_H
#define SIMSERVER_NUMBER_H

#include "Expression.h"

class Number : public Expression {
    double value;

public:
    explicit Number(double num) {
        this->value = num;
    }
    virtual double execute() {
        return this->value;
    }
};

#endif //SIMSERVER_NUMBER_H
