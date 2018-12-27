//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_VAREXPRESSION_H
#define SIMSERVER_VAREXPRESSION_H

#include <string>
#include "Expression.h"
#include "Number.h"

class VarExpression : public Expression {
  string path;
  shared_ptr<Expression> exp;

 public:
  VarExpression(string path) {
    this->exp = make_shared<Number>(0);
    this->path = path;
  }
  VarExpression(shared_ptr<Expression> exp) {
    this->exp = exp;
  }
  virtual double Execute() {
    if (this->exp != nullptr) {
      return this->exp->Execute();
    }
  }
  string GetPath() {
    return this->path;
  };
  shared_ptr<Expression> GetExpression() {
    return this->exp;
  }
  void SetExpression(shared_ptr<Expression> expression) {
    this->exp = expression;
  }
  void SetPath(string newPath) {
    this->path = newPath;
  }
};

#endif //SIMSERVER_VAREXPRESSION_H