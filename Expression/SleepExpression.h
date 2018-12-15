//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_SLEEPEXPRESSION_H
#define SIMSERVER_SLEEPEXPRESSION_H
#include "Expression.h"
#include <unistd.h>
class SleepExpression:public Expression {
    double sleepingTime;
public:
    SleepExpression(double sleepingTime) {
        this->sleepingTime = sleepingTime;
    }

    virtual double Execute() {
        sleep(sleepingTime);
    }
};
#endif //SIMSERVER_SLEEPEXPRESSION_H
