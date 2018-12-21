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
#define FIRST_IMPORTANCE 1
#define SECOND_IMPORTANCE 2
#define THIRD_IMPORTANCE 3
#define OTHER_IMPORTANCE 4

using namespace std;

class ShuntingYard {
    map<string, VarExpression*>* varExpressionMap;
    map<string, int> operatorPrecedence;
public:
    explicit ShuntingYard(map<string, VarExpression*>* stringVarMap) {
        this->varExpressionMap = stringVarMap;
        this->operatorPrecedence = operatorPrecedenceMap();
    }

    Expression *MakeExpression(vector<string> &vec);

private:

    vector<string> GetMathOperatorVector();
    bool IsNumber(string &str);

    bool IsOperator(string &str);
    bool IsMinus(string &str);

    bool IsOpenBracket(string &str);

    bool IsCloseBracket(string &str);

    bool IsVar(string& str);

    bool IsGreaterPrecedence(string &str, string &other);

    Expression* MakeExpressionFromQueue(queue<string> que);

    Expression* BuildOperatorByString(string& str, Expression* right, Expression* left);

    map<string, int>operatorPrecedenceMap();

};


#endif //SIMSERVER_SHUNTINGYARD_H
