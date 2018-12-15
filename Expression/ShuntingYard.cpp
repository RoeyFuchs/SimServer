#include <stack>
#include <queue>
#include <regex>
#include "ShuntingYard.h"
#include "Number.h"


Expression* ShuntingYard::MakeExpression(vector<string>& vec, map<string, VarExpression>& stringVarMap) {
    auto operation = new stack<Expression>();
    auto numbers = new queue<Expression>();

    Expression* A = new Number(5);
    return A ;
}

bool ShuntingYard::isNumber(string &str) {
        return regex_match(str, regex("[0-9]+"));
}

bool ShuntingYard::isOperator(string& str) {
    vector<string> mathOperator = GetMathOperatorVector();
    return (find(mathOperator.begin(), mathOperator.end(), str) != mathOperator.end());

}

bool ShuntingYard::isOpenBracket(string& str) {
    return (str == "(");
}
bool ShuntingYard::isCloseBracket(string& str) {
    return (str == ")");
}

vector<string> ShuntingYard::GetMathOperatorVector() {
    vector<string> A;
    A.emplace_back("+");
    A.emplace_back("-");
    A.emplace_back("*");
    A.emplace_back("/");
    A.emplace_back("%");
    return A;
}



