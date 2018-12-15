//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_OPENDATASERVEREXPRESSION_H
#define SIMSERVER_OPENDATASERVEREXPRESSION_H
#include "Expression.h"

class OpenDataServerExpression: public Expression{
    double  port;
    double samplingRate;
public:
    OpenDataServerExpression(double port, double samplingRate){
        this->port= port;
        this->samplingRate= samplingRate;
    }
    virtual double Execute(){
        return 1;
    }
};
#endif //SIMSERVER_OPENDATASERVEREXPRESSION_H