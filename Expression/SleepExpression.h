//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_SLEEPEXPRESSION_H
#define SIMSERVER_SLEEPEXPRESSION_H
#include "Expression.h"
#include <unistd.h>
#include <thread>
#include <mutex>
class SleepExpression : public Expression {
  shared_ptr<Expression> exp;
  mutex lockThis;
 public:
  SleepExpression(shared_ptr<Expression> exp) {
    this->exp = exp;
  }
  virtual double Execute() {
    this->lockThis.lock();
    int x = this->exp->Execute();
    this_thread::sleep_for(chrono::milliseconds(x));
    this->lockThis.unlock();
  }
  shared_ptr<Expression> GetSleepingTimeExpression() {
    return this->exp;
  }
};
#endif //SIMSERVER_SLEEPEXPRESSION_H
