//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_CONDITIONEXPRESSION_H
#define SIMSERVER_CONDITIONEXPRESSION_H
#include "Expression.h"
#include "ConditionExpression.h"
#include <vector>
#include <string>
class ConditionParser : public Expression {
 protected:
  shared_ptr<ConditionExpression> condition;
  vector<shared_ptr<Expression>> expressions;
 public:
  ConditionParser(shared_ptr<ConditionExpression> condition) {
    this->condition = condition;
  }
  virtual double Execute() {
    if (this->condition->Execute() == 1)
      return 1;
    return 0;
  }
  void AddExpression(shared_ptr<Expression> exp) {
    this->expressions.push_back(exp);
  }

};
#endif //SIMSERVER_CONDITIONEXPRESSION_H
