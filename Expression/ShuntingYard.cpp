#include "ShuntingYard.h"


/**
 * the function recived vector of string, and using the shuting yard algorithm
 * to change it to expression.
 * @param vec vector of string
 * @return pointer to the new expression
 */
shared_ptr<Expression> ShuntingYard::MakeExpression(vector<string> &vec) {
    auto stc = make_shared<stack<string>>();
    auto que = make_shared<queue<string>>();
    //will use to store the previous number (for negative numbers)
    string preToken;
    //for the all token do the shunting yard algorithm.
    for (string &token : vec) {
        //if it's a number or var, push to the queue
        if (IsNumber(token) || IsVar(token)) {
            que->push(token);
            preToken = token;
            continue;
        }
        //if it's (, push to the stack
        if (IsOpenBracket(token)) {
            stc->push(token);
            preToken = token;
            continue;
        }
        //if it's ), move by the algorithm
        if (IsCloseBracket(token)) {
            while (!IsOpenBracket(stc->top())) {
                string top = stc->top();
                stc->pop();
                que->push(top);
            }
            stc->pop();
            continue;
        }
        //if it's operator, move by the algorithm
        if (IsOperator(token)) {
            //using Neg instand of Minus
            if (IsMinus(token) && (!IsNumber(preToken) && !IsVar(preToken))) {
                token = "NEG_SYMBOL"; // negative
            }
            while (!stc->empty() && IsGreaterPrecedence(stc->top(), token)) {
                que->push(stc->top());
                stc->pop();
            }
            stc->push(token);
            preToken = token;
            continue;
        } else {
            throw runtime_error(string(token + " is Invalid"));
        }
    }
    //move the all operation from the stack to the queue
    while (!stc->empty()) {
        que->push(stc->top());
        stc->pop();
    }

    return MakeExpressionFromQueue(*que);
}
/**
 * check if a string is a number
 * @param str the string to check
 * @return true or false
 */
bool ShuntingYard::IsNumber(string &str) {
    return regex_match(str, regex("^(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
}
/**
 * check if a string is an operator
 * @param str the string to check
 * @return true or false
 */
bool ShuntingYard::IsOperator(string &str) {
    vector<string> mathOperator = GetMathOperatorVector();
    return (find(mathOperator.begin(), mathOperator.end(), str) != mathOperator.end());

}
/**
 * check if a string is an open bracket
 * @param str the string to check
 * @return true or false
 */
bool ShuntingYard::IsOpenBracket(string &str) {
    return (str == "(");
}
/**
 * check if a string is a a close breacket
 * @param str the string to check
 * @return true or false
 */
bool ShuntingYard::IsCloseBracket(string &str) {
    return (str == ")");
}
/**
 * check if a string is a var
 * @param str the string to check
 * @return true or false
 */
bool ShuntingYard::IsVar(string& str) {
    return this->expressionMaps->VarExists(str);
}
/**
 * the function return a vector with the supported operators.
 * @return vector of the operators
 */
vector<string> ShuntingYard::GetMathOperatorVector() {
    vector<string> A;
    A.emplace_back("+");
    A.emplace_back("-");
    A.emplace_back("*");
    A.emplace_back("/");
    A.emplace_back("%");
    A.emplace_back("NEG_SYMBOL");
    return A;
}
/**
 * check if a string is a minus.
 * @param str the string to check
 * @return true or false
 */
bool ShuntingYard::IsMinus(string &str) {
    return (str == "-");
}
/**
 * check an operator have a greater precedence with another operator.
 * @param str first operator
 * @param other seconde operator
 * @return true or false
 */
bool ShuntingYard::IsGreaterPrecedence(string &str, string &other) {
    return (this->operatorPrecedence[str] <= this->operatorPrecedence[other]);
}
/**
 * this function will receive a queue with expressions in postfix, and return one expression
 * @param que the queue
 * @return pointer to new expression
 */
shared_ptr<Expression> ShuntingYard::MakeExpressionFromQueue(queue<string> que) {
    auto stc = stack<shared_ptr<Expression>>();
    //do the algorithm to the all expression in the queue
    while (!que.empty()) {
        //if it's a number, create a number object and push to the stack
        if (IsNumber(que.front())) {
            shared_ptr<Expression> A = make_shared<Number>(stod(que.front()));
            stc.push(A);
            que.pop();
            continue;
        }
        //if it's var, push to the stack
        if(IsVar(que.front())) {
            stc.push(this->expressionMaps->GetExpressionByName(que.front()));
            que.pop();
        //if it's operator, create the operator with the 2 top expression in the stack
        } else {
            if (que.front()=="NEG_SYMBOL") {
                shared_ptr<Expression> A = make_shared<Neg>(stc.top());
                stc.pop();
                stc.push(A);
                que.pop();
            } else {
                shared_ptr<Expression> right = stc.top();
                stc.pop();
                shared_ptr<Expression> left = stc.top();
                stc.pop();
                stc.push(BuildOperatorByString(que.front(), right, left));
                que.pop();
            }
        }
    }
    return stc.top();

}
/**
 * the function build an operator expression
 * @param str the operator
 * @param right right expression
 * @param left left expression
 * @return operator expression
 */
shared_ptr<Expression> ShuntingYard::BuildOperatorByString(string &str, shared_ptr<Expression> right, shared_ptr<Expression> left) {
    if (str == "+") {
        return make_shared<Plus>(left, right);
    }
    if (str == "-") {
        return make_shared<Minus>(left, right);
    }
    if (str == "*") {
        return make_shared<Mult>(left, right);
    }
    if (str == "/") {
        return make_shared<Div>(left, right);
    }
    if (str == "%") {
        return make_shared<Modulo>(left, right);
    }
    throw runtime_error(string("Invalid operator"));
}

/**
 * the function return a map with orecedence of math operators
 * @return the map
 */
unordered_map<string, int> ShuntingYard::operatorPrecedenceMap() {
    unordered_map<string, int> A;
    A[NEG_SYMBOL] = FIRST_IMPORTANCE;
    A["*"] = SECOND_IMPORTANCE;
    A["/"] = SECOND_IMPORTANCE;
    A["%"] = SECOND_IMPORTANCE;
    A["+"] = THIRD_IMPORTANCE;
    A["-"] = THIRD_IMPORTANCE;
    A["("] = OTHER_IMPORTANCE;
    A[")"] = OTHER_IMPORTANCE;
    return A;
}



