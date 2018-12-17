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
    ConditionExpression condition;
    bool isComplete;
    std::vector<Expression*> commands;
public:
    ConditionParser(ConditionExpression condition){
        this->isComplete= false;
        this->condition=condition;
    }
    void SetIsComplete(bool isComplete){
        this->isComplete=isComplete;
    }
    bool GetIsComplete(){
        return this->isComplete;
    }
    void AddCommand(Expression* exp){
        this->commands.push_back(exp);
    }
    bool Evaluate(){
        if(this->condition.Execute()==1)
            return true;
        return false;
    }
};
#endif //SIMSERVER_CONDITIONEXPRESSION_H
