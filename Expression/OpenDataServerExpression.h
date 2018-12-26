//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_OPENDATASERVEREXPRESSION_H
#define SIMSERVER_OPENDATASERVEREXPRESSION_H
#include "Expression.h"
#include "ExpressionMaps.h"
#include "../Utils/Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <thread>

#include <sys/socket.h>
#define BUFFER_SIZE 512
#define NEW_LINE_CHAR '\n'
#define DELIMITER ','
#define MICRO 1000000

class OpenDataServerExpression : public Expression {

  shared_ptr<Expression> port;
  shared_ptr<Expression> samplingRate;
  shared_ptr<ExpressionMaps> maps;
  unordered_map<int, string> xmlOrder;
  int sockfd;

 public:
  OpenDataServerExpression(shared_ptr<Expression> port,
                           shared_ptr<Expression> samplingRate,
                           shared_ptr<ExpressionMaps> maps) {
    this->port = port;
    this->samplingRate = samplingRate;
    this->maps = maps;
    this->xmlOrder = Utils::GetXmlOrder();
  }
  virtual double Execute();

  void ReadData(int newsockfd);

  shared_ptr<Expression> GetPort() {
    return this->port;
  };
  shared_ptr<Expression> GetSamplingRate() {
    return this->samplingRate;
  }

  ~OpenDataServerExpression() {
    close(this->sockfd);
  }
};
#endif //SIMSERVER_OPENDATASERVEREXPRESSION_H