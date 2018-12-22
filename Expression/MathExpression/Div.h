#ifndef SIMSERVER_DIV_H
#define SIMSERVER_DIV_H

#include <string>
#include <stdexcept>
#include "../BinaryExpression.h"

using namespace std;

class Div : public BinaryExpression {
 public:
  Div(shared_ptr<Expression> left, shared_ptr<Expression> right) : BinaryExpression(left, right) {}

  double Execute() override {
    double right = BinaryExpression::GetRight()->Execute();
    if (right == 0) {
      throw runtime_error(string("Can't Divide By Zero"));
    }
    return BinaryExpression::GetLeft()->Execute() / right;
  }

};

#endif //SIMSERVER_DIV_H
