//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_VAREXPRESSION_H
#define SIMSERVER_VAREXPRESSION_H

#include <string>
#include "Expression.h"

class VarExpression: public Expression{
    std::string path;
    Expression*  exp;
public:
    VarExpression(std::string path){
        this->path= path;
    }
    VarExpression(Expression* exp){
        this->exp= exp;
    }
    virtual double Execute(){
        return this->exp->Execute();
    }
};

#endif //SIMSERVER_VAREXPRESSION_H
