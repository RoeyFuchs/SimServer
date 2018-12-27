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
#include <thread>
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>

#include <string.h>
#include <mutex>





class ConnectExpression : public Expression {
  shared_ptr<Expression> port;
  string ip;
  string currentCommandl;
  int sockfd;
  mutex lockNewCommand;
 public:
  ConnectExpression(string ip, shared_ptr<Expression> port) {
    this->ip = ip;
    this->port = port;
  }
  virtual double Execute();

  void GetCommand(string bind, double value) {
    string str = string(SET_COMMAND) + " " + bind + " " + to_string(value) + string(END_LINE);
    this->lockNewCommand.lock();
    this->currentCommandl = str;
    thread t2(&ConnectExpression::SendData, this);
    this->lockNewCommand.unlock();
    t2.detach();

  }

  void SendData();

  shared_ptr<Expression> GetPort() {
    return this->port;
  }
  string GetIp() {
    return this->ip;
  }

  ~ConnectExpression() {
    close(this->sockfd);
  }
};

#endif //SIMSERVER_CONNECTEXPRESSION_H