#ifndef SIMSERVER_NEG_H
#define SIMSERVER_NEG_H

#include "../Expression.h"
#include "../UnaryExpression.h"

class Neg : public UnaryExpression {
 public:
  Neg(shared_ptr<Expression> exp) : UnaryExpression(exp) {}

  double Execute() override {
    return -UnaryExpression::GetLeaf()->Execute();
  }
};

#endif //SIMSERVER_NEG_H
