#ifndef SIMSERVER_BINARYEXPRESSION_H
#define SIMSERVER_BINARYEXPRESSION_H

#include "Expression.h"

class BinaryExpression : public Expression {
    shared_ptr<Expression> leftLeaf;
    shared_ptr<Expression> rightLeaf;
protected:
    //will use for +,-,*,/ ...
    BinaryExpression(shared_ptr<Expression> left, shared_ptr<Expression> right) : leftLeaf(left), rightLeaf(right){
    }

    shared_ptr<Expression> GetLeft() {
        return this->leftLeaf;
    }
    shared_ptr<Expression> GetRight() {
        return this->rightLeaf;
    }
    virtual double Execute() = 0;
};

#endif //SIMSERVER_BINARYEXPRESSION_H
