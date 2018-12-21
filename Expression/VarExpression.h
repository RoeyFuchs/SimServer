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
        if(this->exp!= nullptr){
            return this->exp->Execute();
        }
    }
    std::string GetPath(){
        return this->path;
    };
    Expression* GetExpression(){
        return this->exp;
    }
    void SetExpression(Expression* exp){
        this->exp=exp;
    }
    void SetPath(std::string path){
        this->path=path;
    }
};

#endif //SIMSERVER_VAREXPRESSION_H