#ifndef SIMSERVER_SHUNTINGYARD_H
#define SIMSERVER_SHUNTINGYARD_H

#include <vector>
#include <map>
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

#define NEG_SYMBOL "_"

using namespace std;

class ShuntingYard {
    map<string, VarExpression*>* varExpressionMap;
public:
    explicit ShuntingYard(map<string, VarExpression*>* stringVarMap) {
        this->varExpressionMap = stringVarMap;
    }

    Expression *MakeExpression(vector<string> &vec);

private:

    vector<string> GetMathOperatorVector();

    bool isNumber(string &str);

    bool isOperator(string &str);
    bool isMinus(string &str);

    bool isOpenBracket(string &str);

    bool isCloseBracket(string &str);

    bool isVar(string& str);

    bool isGreaterPrecedence(string &str, string &other);

    Expression* MakeExpressionFromQueue(queue<string> que);

    Expression* BuildOperatorByString(string& str, Expression* right, Expression* left);

};


#endif //SIMSERVER_SHUNTINGYARD_H
