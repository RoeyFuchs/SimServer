//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_PRINTEXPRESSION_H
#define SIMSERVER_PRINTEXPRESSION_H

#include <iostream>
#include "Expression.h"
using namespace std;
#endif //SIMSERVER_PRINTEXPRESSION_H
class PrintExpression:public Expression{
    Expression* exp;
    string str;
public:
    PrintExpression(Expression *exp){
        this->exp=exp;
    }
    PrintExpression(string str){
        this->exp= nullptr;
        this->str=str;
    }
    virtual double Execute(){
        if(this->exp!= nullptr) {
            cout << this->exp->Execute() << endl;
        } else{
            cout<<this->str<<endl;
        }
    }
};