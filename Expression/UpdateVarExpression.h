//
// Created by stav on 12/24/18.
//

#ifndef SIMSERVER_UPDATEVAREXPRESSION_H
#define SIMSERVER_UPDATEVAREXPRESSION_H
#include "Expression.h"
#include "ExpressionMaps.h"
#include "ConnectExpression.h"

class UpdateVarExpression : public Expression {
  shared_ptr<Expression> expressionToReplace;
  shared_ptr<VarExpression> varExp;
  shared_ptr<ConnectExpression> connectExp;
  string newPath;
 public:
  UpdateVarExpression(shared_ptr<Expression> exp, shared_ptr<VarExpression> varExp,
      shared_ptr<ConnectExpression> connectExp) {
    this->expressionToReplace = exp;
    this->varExp = varExp;
    this->connectExp = connectExp;
  }
  UpdateVarExpression(string path, shared_ptr<VarExpression> varExp, shared_ptr<ConnectExpression> connectExp) {
    this->newPath = path;
    this->varExp = varExp;
    this->connectExp = connectExp;
    this->expressionToReplace = nullptr;
  }
  virtual double Execute() {
    if (expressionToReplace != nullptr) {
      this->varExp->SetExpression(make_shared<Number>(expressionToReplace->Execute()));
      if(!this->varExp->GetPath().empty()) {
        this->connectExp->GetCommand(this->varExp->GetPath(), this->varExp->Execute());
      }
      return this->varExp->Execute();
    } else {
      this->varExp->SetPath(this->newPath);
      return this->varExp->Execute();
    }
  }
};
#endif //SIMSERVER_UPDATEVAREXPRESSION_H
