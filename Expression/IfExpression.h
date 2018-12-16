//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_IFEXPRESSION_H
#define SIMSERVER_IFEXPRESSION_H

#include "ConditionParser.h"

class IfExpression: ConditionParser{
    virtual double Execute(){
        if (this->Evaluate()){
            //TODO iterate on each command
        }
    }
};
#endif //SIMSERVER_IFEXPRESSION_H
