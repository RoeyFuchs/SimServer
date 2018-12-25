//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_CONNECTEXPRESSION_H
#define SIMSERVER_CONNECTEXPRESSION_H
#define BUFFER_SIZE_OUT 128

#include <string>
#include <deque>
#include "Expression.h"

#endif //SIMSERVER_CONNECTEXPRESSION_H
class ConnectExpression : public Expression {
  shared_ptr<Expression> port;
  string ip;
  deque<string> deq;
 public:
  ConnectExpression(string ip, shared_ptr<Expression> port) {
    this->ip = ip;
    this->port = port;
  }
  virtual double Execute();

  shared_ptr<Expression> GetPort() {
    return this->port;
  }
  string GetIp() {
    return this->ip;
  }
};