//
// Created by stav on 12/17/18.
//

#ifndef SIMSERVER_WHILEEXPRESSION_H
#define SIMSERVER_WHILEEXPRESSION_H
#include "ConditionParser.h"

class WhileExpression: ConditionParser{
    virtual double Execute(){
        while (this->Execute()){
            for (int i = 0; i < this->expressions.size() ; ++i) {
                this->expressions[i]->Execute();
            }
        }
    }
};
#endif //SIMSERVER_WHILEEXPRESSION_H
