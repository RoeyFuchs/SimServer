//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_VAREXPRESSION_H
#define SIMSERVER_VAREXPRESSION_H

#include <string>
#include "Expression.h"

class VarExpression: public Expression{
    std::string path;
    double  value;
public:
    VarExpression(std::string path){
        this->path= path;
    }
    VarExpression(double value){
        this->value= value;
    }
    virtual double Execute(){
        return this->value;
    }
};

#endif //SIMSERVER_VAREXPRESSION_H
