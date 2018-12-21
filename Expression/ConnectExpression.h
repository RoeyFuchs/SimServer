//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_CONNECTEXPRESSION_H
#define SIMSERVER_CONNECTEXPRESSION_H

#include <string>
#include "Expression.h"

#endif //SIMSERVER_CONNECTEXPRESSION_H
class ConnectExpression: public Expression{
    Expression* port;
    std::string ip;
public:
    ConnectExpression(std::string ip, Expression* port){
        this->ip= ip;
        this->port= port;
    }
    virtual double Execute(){
        return 1;
    }
    Expression* GetPort(){
        return this->port;
    }
    string GetIp(){
        return this->ip;
    }
};