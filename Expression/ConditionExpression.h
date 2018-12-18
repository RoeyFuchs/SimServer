//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_CONDITIONEVALUATION_H
#define SIMSERVER_CONDITIONEVALUATION_H

#include "Expression.h"
#include <string>

class ConditionExpression {
private:
    std::string conditionOperator;
    Expression* leftExp;
    Expression* rightExp;
public:
    ConditionExpression(std::string conditionOperator, Expression* leftExp, Expression* rightExp){
        this->conditionOperator= conditionOperator;
        this->leftExp= leftExp;
        this->rightExp= rightExp;
    }
    virtual double Execute();
};


#endif //SIMSERVER_CONDITIONEVALUATION_H