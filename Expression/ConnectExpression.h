//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_CONNECTEXPRESSION_H
#define SIMSERVER_CONNECTEXPRESSION_H

#include <string>
#include "Expression.h"

#endif //SIMSERVER_CONNECTEXPRESSION_H
class ConnectExpression : public Expression {
  shared_ptr<Expression> port;
  string ip;
 public:
  ConnectExpression(string ip, shared_ptr<Expression> port) {
    this->ip = ip;
    this->port = port;
  }
  virtual double Execute() {
    return 1;
  }
  shared_ptr<Expression> GetPort() {
    return this->port;
  }
  string GetIp() {
    return this->ip;
  }
};