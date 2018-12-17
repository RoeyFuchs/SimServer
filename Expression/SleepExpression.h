//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_SLEEPEXPRESSION_H
#define SIMSERVER_SLEEPEXPRESSION_H
#include "Expression.h"
#include <unistd.h>
class SleepExpression:public Expression {
    Expression* exp;
public:
    SleepExpression(Expression* exp) {
        this->exp = exp;
    }
    virtual double Execute() {
        sleep(exp->Execute());
    }
};
#endif //SIMSERVER_SLEEPEXPRESSION_H
