//
// Created by stav on 12/24/18.
//

#ifndef SIMSERVER_UPDATEVAREXPRESSION_H
#define SIMSERVER_UPDATEVAREXPRESSION_H
#include "Expression.h"
#include "ExpressionMaps.h"
class UpdateVarExpression:public Expression{
    shared_ptr<Expression> expressionToReplace;
    shared_ptr<VarExpression> varExp;
    string newPath;
public:
    UpdateVarExpression(shared_ptr<Expression> exp,shared_ptr<VarExpression> varExp) {
        this->expressionToReplace = exp;
        this->varExp=varExp;
    }
    UpdateVarExpression(string path,shared_ptr<VarExpression> varExp) {
        this->newPath = path;
        this->varExp=varExp;
        this->expressionToReplace= nullptr;
    }
    virtual double Execute() {
        if(expressionToReplace!= nullptr) {
            this->varExp->SetExpression(expressionToReplace);
            return this->varExp->Execute();
        }else{
            this->varExp->SetPath(this->newPath);
            return this->varExp->Execute();
        }
    }
};
#endif //SIMSERVER_UPDATEVAREXPRESSION_H
