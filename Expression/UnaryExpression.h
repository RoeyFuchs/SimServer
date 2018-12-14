#include "Expression.h"

#ifndef SIMSERVER_UNARYEXPRESSION_H
#define SIMSERVER_UNARYEXPRESSION_H

#endif //SIMSERVER_UNARYEXPRESSION_H

class UnaryExpression : public Expression {
    Expression* leaf;
protected:
    explicit UnaryExpression(Expression* leaf) {
        this->leaf = leaf;
    }
    virtual double Execute() = 0;

    Expression* GetLeaf() {
        return this->leaf;
    }
};