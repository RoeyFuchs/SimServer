#ifndef SIMSERVER_SHUNTINGYARD_H
#define SIMSERVER_SHUNTINGYARD_H

#include <vector>
#include <unordered_map>
#include "Expression.h"
#include "VarExpression.h"
#include <stack>
#include <queue>
#include <regex>
#include "Number.h"
#include "string"
#include "MathExpression/Plus.h"
#include "MathExpression/Div.h"
#include "MathExpression/Modulo.h"
#include "MathExpression/Minus.h"
#include "MathExpression/Mult.h"
#include "MathExpression/Neg.h"
#include "ExpressionMaps.h"

#define NEG_SYMBOL "_"
#define FIRST_IMPORTANCE 1
#define SECOND_IMPORTANCE 2
#define THIRD_IMPORTANCE 3
#define OTHER_IMPORTANCE 4

using namespace std;

class ShuntingYard {
  shared_ptr<ExpressionMaps> expressionMaps;
  unordered_map<string, int> operatorPrecedence;
 public:
  explicit ShuntingYard(shared_ptr<ExpressionMaps> expressionMaps) {
    this->expressionMaps = expressionMaps;
    this->operatorPrecedence = operatorPrecedenceMap();
  }

  shared_ptr<Expression> MakeExpression(vector<string> &vec);

 private:

  vector<string> GetMathOperatorVector();
  bool IsNumber(string &str);

  bool IsOperator(string &str);
  bool IsMinus(string &str);

  bool IsOpenBracket(string &str);

  bool IsCloseBracket(string &str);

  bool IsVar(string &str);

  bool IsGreaterPrecedence(string &str, string &other);

  shared_ptr<Expression> MakeExpressionFromQueue(queue<string> que);

  shared_ptr<Expression> BuildOperatorByString(string &str, shared_ptr<Expression> right, shared_ptr<Expression> left);

  unordered_map<string, int> operatorPrecedenceMap();

};

#endif //SIMSERVER_SHUNTINGYARD_H
