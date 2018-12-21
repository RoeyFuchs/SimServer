//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_OPENDATASERVEREXPRESSION_H
#define SIMSERVER_OPENDATASERVEREXPRESSION_H
#include "Expression.h"

class OpenDataServerExpression: public Expression{
    Expression*  port;
    Expression* samplingRate;
public:
    OpenDataServerExpression(Expression* port, Expression* samplingRate){
        this->port= port;
        this->samplingRate= samplingRate;
    }
    virtual double Execute(){
        return 1;
    }
    Expression* GetPort(){
        return this->port;
    };
    Expression* GetSamplingRate(){
        return  this->samplingRate;
    }
};
#endif //SIMSERVER_OPENDATASERVEREXPRESSION_H