//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_IFEXPRESSION_H
#define SIMSERVER_IFEXPRESSION_H

#include "ConditionParser.h"
#include <iostream>
class IfExpression : public ConditionParser {
 public:

  IfExpression(shared_ptr<ConditionExpression> condition) : ConditionParser(condition) {}

  virtual double Execute() {
    if (this->condition->Execute()) {
      for (int i = 0; i < this->expressions.size(); ++i) {
          if(this->expressions[i]!= nullptr) {
              this->expressions[i]->Execute();
          }
      }
    }
  }
};
#endif //SIMSERVER_IFEXPRESSION_H
