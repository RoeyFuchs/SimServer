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

using namespace std;

class ShuntingYard {
public:
    ShuntingYard() = default;

    Expression *MakeExpression(vector<string> &vec, map<string, VarExpression*> &stringVarMap);

    vector<string> GetMathOperatorVector();

    bool isNumber(string &str);

    bool isOperator(string &str);
    bool isMinus(string &str);

    bool isOpenBracket(string &str);

    bool isCloseBracket(string &str);

    bool isVar(string& str, map<string, VarExpression*>& stringVarMap);

    bool isGreaterPrecedence(string &str, string &other);

    Expression* MakeExpressionFromQueue(queue<string> que, map<string, VarExpression*>& stringVarMap);

    Expression* BuildOperatorByString(string& str, Expression* right, Expression* left);



};


#endif //SIMSERVER_SHUNTINGYARD_H
