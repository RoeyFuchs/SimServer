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
  bool isComplete;
  vector<shared_ptr<Expression>> expressions;
 public:
  ConditionParser(shared_ptr<ConditionExpression> condition) {
    this->isComplete = false;
    this->condition = condition;
  }
  virtual double Execute() {
    if (this->condition->Execute() == 1)
      return 1;
    return 0;
  }
  void SetIsComplete(bool isComplete) {
    this->isComplete = isComplete;
  }
  bool GetIsComplete() {
    return this->isComplete;
  }
  shared_ptr<Expression> GetLastExp() {
    return this->expressions[expressions.size() - 1];
  }
  shared_ptr<Expression> GetExp(int index) {
    if (index >= 0 && index < expressions.size() - 1) {
      return this->expressions[index];
    }
    return nullptr;
  }
  void AddExpression(shared_ptr<Expression> exp) {
    this->expressions.push_back(exp);
  }
  int GetExpressionsSize(){
    return this->expressions.size();
  }

};
#endif //SIMSERVER_CONDITIONEXPRESSION_H
