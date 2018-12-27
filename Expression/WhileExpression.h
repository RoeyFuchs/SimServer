//
// Created by stav on 12/17/18.
//

#ifndef SIMSERVER_WHILEEXPRESSION_H
#define SIMSERVER_WHILEEXPRESSION_H
#include "ConditionParser.h"
#include <iostream>
class WhileExpression: public ConditionParser{
public:
    WhileExpression(shared_ptr<ConditionExpression> condition):ConditionParser(condition){}

    virtual double Execute(){
        while (this->condition->Execute()){
            for (int i = 0; i < this->expressions.size() ; ++i) {
                if(this->expressions[i]!= nullptr) {
                    this->expressions[i]->Execute();
                }
            }
        }
    }
};
#endif //SIMSERVER_WHILEEXPRESSION_H
