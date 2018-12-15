#ifndef SIMSERVER_SHUNTINGYARD_H
#define SIMSERVER_SHUNTINGYARD_H

#include <vector>
#include <map>
#include "Expression.h"
#include "VarExpression.h"

using namespace std;

class ShuntingYard {
public:
    ShuntingYard() = default;

    Expression *MakeExpression(vector<string> &vec, map<string, VarExpression> &stringVarMap);

    vector<string> GetMathOperatorVector();

    bool isNumber(string &str);

    bool isOperator(string &str);

    bool isOpenBracket(string &str);

    bool isCloseBracket(string &str);


};


#endif //SIMSERVER_SHUNTINGYARD_H
