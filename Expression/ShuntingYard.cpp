#include "ShuntingYard.h"


Expression *ShuntingYard::MakeExpression(vector<string> &vec) {
    auto stc = new stack<string>();
    auto que = new queue<string>();
    //will use to store the previous number (for negative numbers)
    string preToken;
    //for the all token do the shunting yard algorithm.
    for (string &token : vec) {
        //if it's a number or var, push to the queue
        if (isNumber(token) || isVar(token)) {
            que->push(token);
            preToken = token;
            continue;
        }
        //if it's (, push to the stack
        if (isOpenBracket(token)) {
            stc->push(token);
            preToken = token;
            continue;
        }
        //if it's ), move by the algorithm
        if (isCloseBracket(token)) {
            while (!isOpenBracket(stc->top())) {
                string top = stc->top();
                stc->pop();
                que->push(top);
            }
            stc->pop();
            continue;
        }
        //if it's operator, move by the algorithm
        if (isOperator(token)) {
            while (!stc->empty() && isGreaterPrecedence(stc->top(), token)) {
                que->push(stc->top());
                stc->pop();
            }
            //using Minus instand of Neg
            if (isMinus(token) && (!isNumber(preToken) || isVar(preToken))) {
                que->push("0");
            }
            stc->push(token);
            preToken = token;
            continue;
        }
    }
    //move the all operation from the stack to the queue
    while (!stc->empty()) {
        que->push(stc->top());
        stc->pop();
    }

    return MakeExpressionFromQueue(*que);
}

bool ShuntingYard::isNumber(string &str) {
    return regex_match(str, regex("[0-9]+"));
}

bool ShuntingYard::isOperator(string &str) {
    vector<string> mathOperator = GetMathOperatorVector();
    return (find(mathOperator.begin(), mathOperator.end(), str) != mathOperator.end());

}

bool ShuntingYard::isOpenBracket(string &str) {
    return (str == "(");
}

bool ShuntingYard::isCloseBracket(string &str) {
    return (str == ")");
}

bool ShuntingYard::isVar(string& str) {
    return (this->varExpressionMap.count(str) != 0);
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

bool ShuntingYard::isMinus(string &str) {
    return (str == "-");
}

bool ShuntingYard::isGreaterPrecedence(string &str, string &other) {
    return (((str == "*" || str == "/") && (other == "+" || other == "-")) ||
    (str=="-" && other =="-") || (str=="-" && other=="+"));
}
//this function will receive a queue with expressions in postfix, and return one expression
Expression *ShuntingYard::MakeExpressionFromQueue(queue<string> que) {
    auto stc = stack<Expression *>();
    //do the algorithm to the all expression in the queue
    while (!que.empty()) {
        //if it's a number, create a number object and push to the stack
        if (isNumber(que.front())) {
            Expression *A = new Number(stod(que.front()));
            stc.push(A);
            que.pop();
            continue;
        }
        //if it's var, push to the stack
        if(isVar(que.front())) {
            stc.push((*this->varExpressionMap)[que.front()]);
            que.pop();
        //if it's operator, create the operator with the 2 top expression in the stack
        } else {
            Expression *right = stc.top();
            stc.pop();
            Expression *left = stc.top();
            stc.pop();
            stc.push(BuildOperatorByString(que.front(), right, left));
            que.pop();
        }
    }
    return stc.top();

}

Expression *ShuntingYard::BuildOperatorByString(string &str, Expression *right, Expression *left) {
    if (str == "+") {
        return new Plus(left, right);
    }
    if (str == "-") {
        return new Minus(left, right);
    }
    if (str == "*") {
        return new Mult(left, right);
    }
    if (str == "/") {
        return new Div(left, right);
    }
    if (str == "%") {
        return new Modulo(left, right);
    }
    throw runtime_error(string("Invalid operator"));
}



