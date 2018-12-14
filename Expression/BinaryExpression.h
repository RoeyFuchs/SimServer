#ifndef SIMSERVER_BINARYEXPRESSION_H
#define SIMSERVER_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
    Expression* leftLeaf;
    Expression* rightLeaf;
protected:
    //will use for +,-,*,/ ...
    BinaryExpression(Expression* left, Expression* right) : leftLeaf(left), rightLeaf(right){
    }

    Expression* GetLeft() {
        return this->leftLeaf;
    }
    Expression* GetRight() {
        return this->rightLeaf;
    }
    virtual double Execute() = 0;
};

#endif //SIMSERVER_BINARYEXPRESSION_H
