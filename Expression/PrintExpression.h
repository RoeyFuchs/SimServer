//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_PRINTEXPRESSION_H
#define SIMSERVER_PRINTEXPRESSION_H

#include <iostream>
#include "Expression.h"
#endif //SIMSERVER_PRINTEXPRESSION_H

class PrintExpression : public Expression {
  shared_ptr<Expression> exp;
  string str;
 public:
  PrintExpression(shared_ptr<Expression> exp) {
    this->exp = exp;
  }
  PrintExpression(string str) {
    this->exp = nullptr;
    this->str = str;
  }
  virtual double Execute() {
    if (this->exp != nullptr) {
      cout << this->exp->Execute() << endl;
    } else {
      cout << this->str << endl;
    }
  }
};