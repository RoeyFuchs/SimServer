#include "Expression.h"

#ifndef SIMSERVER_UNARYEXPRESSION_H
#define SIMSERVER_UNARYEXPRESSION_H

#endif //SIMSERVER_UNARYEXPRESSION_H

class UnaryExpression : public Expression {
  shared_ptr<Expression> leaf;
 protected:
  explicit UnaryExpression(shared_ptr<Expression> leaf) {
    this->leaf = leaf;
  }
  virtual double Execute() = 0;

  shared_ptr<Expression> GetLeaf() {
    return this->leaf;
  }
};