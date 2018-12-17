//
// Created by stav on 12/16/18.
//

#include "ConditionExpression.h"

 double ConditionExpression::Execute() {
    if(this->conditionOperator==">"){
        return (this->leftExp->Execute()>this->rightExp->Execute());
    } else  if(this->conditionOperator=="<"){
        return (this->leftExp->Execute()<this->rightExp->Execute());
    }else  if(this->conditionOperator==">="){
        return (this->leftExp->Execute()>=this->rightExp->Execute());
    }else  if(this->conditionOperator=="<="){
        return (this->leftExp->Execute()<=this->rightExp->Execute());
    }else  if(this->conditionOperator=="=="){
        return (this->leftExp->Execute()==this->rightExp->Execute());
    }else  if(this->conditionOperator=="!="){
        return (this->leftExp->Execute()!=this->rightExp->Execute());
    }
}