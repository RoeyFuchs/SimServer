#ifndef SIMSERVER_MULT_H
#define SIMSERVER_MULT_H

#include "../BinaryExpression.h"

class Mult : public BinaryExpression {
 public:
  Mult(shared_ptr<Expression> left, shared_ptr<Expression> right) : BinaryExpression(left, right) {}

  double Execute() override {
    return BinaryExpression::GetLeft()->Execute() * BinaryExpression::GetRight()->Execute();
  }

};

#endif //SIMSERVER_MULT_H
