#ifndef SIMSERVER_PLUS_H
#define SIMSERVER_PLUS_H

#include "../BinaryExpression.h"

class Plus : public BinaryExpression {
 public:
  Plus(shared_ptr<Expression> left, shared_ptr<Expression> right) : BinaryExpression(left, right) {}

  double Execute() override {
    return (BinaryExpression::GetLeft()->Execute() + BinaryExpression::GetRight()->Execute());
  }

};

#endif //SIMSERVER_PLUS_H
