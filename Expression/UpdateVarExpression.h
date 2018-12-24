//
// Created by stav on 12/24/18.
//

#ifndef SIMSERVER_UPDATEVAREXPRESSION_H
#define SIMSERVER_UPDATEVAREXPRESSION_H
#include "Expression.h"
#include "ExpressionMaps.h"
class UpdateVarExpression:public Expression{
    shared_ptr<Expression> exp;
    shared_ptr<VarExpression> varExp;
public:
    UpdateVarExpression(shared_ptr<Expression> exp,shared_ptr<VarExpression> varExp) {
        this->exp = exp;
        this->varExp=varExp;
    }
    virtual double Execute() {
        if(this->varExp->GetExpression()!= nullptr) {
            this->varExp->SetExpression(exp);
            return this->varExp->Execute();
        }
    }
};
#endif //SIMSERVER_UPDATEVAREXPRESSION_H
