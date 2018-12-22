//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_SLEEPEXPRESSION_H
#define SIMSERVER_SLEEPEXPRESSION_H
#include "Expression.h"
#include <unistd.h>
class SleepExpression : public Expression {
  shared_ptr<Expression> exp;
 public:
  SleepExpression(shared_ptr<Expression> exp) {
    this->exp = exp;
  }
  virtual double Execute() {
    sleep(exp->Execute());
  }
  shared_ptr<Expression> GetSleepingTimeExpression() {
    return this->exp;
  }
};
#endif //SIMSERVER_SLEEPEXPRESSION_H
