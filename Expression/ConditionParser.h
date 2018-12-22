//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_CONDITIONEXPRESSION_H
#define SIMSERVER_CONDITIONEXPRESSION_H
#include "Expression.h"
#include "ConditionExpression.h"
#include <vector>
#include <string>
class ConditionParser:public Expression{
protected:
    ConditionExpression* condition;
    bool isComplete;
    std::vector<Expression*> expressions;
public:
    ConditionParser(ConditionExpression* condition){
        this->isComplete= false;
        this->condition=condition;
    }
    virtual double Execute(){
        if(this->condition->Execute()==1)
            return 1;
        return 0;
    }
    void SetIsComplete(bool isComplete){
        this->isComplete= isComplete;
    }
    bool GetIsComplete() {
        return this->isComplete;
    }
    Expression* GetLastExp(){
        return this->expressions[expressions.size()-1];
    }
    Expression* GetExp(int index){
        if(index>=0&& index<expressions.size()-1) {
            return this->expressions[index];
        }
        return nullptr;
    }
    void AddExpression(Expression* exp){
        this->expressions.push_back(exp);
    }
};
#endif //SIMSERVER_CONDITIONEXPRESSION_H
