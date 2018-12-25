//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_CONNECTEXPRESSION_H
#define SIMSERVER_CONNECTEXPRESSION_H
#define BUFFER_SIZE_OUT 128
#define SET_COMMAND "set"
#define END_LINE "\r\n"
#include <string>
#include <deque>
#include <iostream>
#include "Expression.h"
#include <mutex>
#include <thread>
#include <condition_variable>

#endif //SIMSERVER_CONNECTEXPRESSION_H

mutex m;
condition_variable cv;

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

  void GetCommand(string bind, double value) {
    string str = string(SET_COMMAND) + " " + bind + " " + to_string(value) + string(END_LINE);
    this->deq.push_back(bind);
  }

  shared_ptr<Expression> GetPort() {
    return this->port;
  }
  string GetIp() {
    return this->ip;
  }
};