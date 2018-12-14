//
// Created by roey on 12/14/18.
//

#include <string>
#include <vector>
#include <iostream>
#include "../Expression/Expression.h"
#include "../Expression/Expression.h"
#include "../Expression/Number.h"
#include "../Expression/MathExpression/Plus.h"
#include "../Expression/MathExpression/Minus.h"
#include "../Expression/MathExpression/Mult.h"
#include "../Expression/MathExpression/Div.h"

#ifndef SIMSERVER_NUMBERTEST_H

using namespace std;

static void NumTest() {
    int counter = 1;

    string success = "test" + to_string(counter) + " passed";
    string failed = "test" + to_string(counter) + " failed";
    string msg;

    auto *l = new vector<Expression>;
    l->push_back(Number(5.5));  // 1
    l->push_back(Number(6));  // 2
    l->push_back(Number(9));  // 3
    l->push_back(Number(150.2)); // 4
    l->push_back(Number(39.3)); // 5
    l->push_back(Number(-5.0)); // 6


//test 1
    Plus(Number(6), Number(1)).Execute() == (11.5) ? msg = success : msg = failed;
    cout << msg << endl;
    ++counter;
//test 2
    Minus(l->at(0), l->at(1)).Execute() == (-0.5) ? msg = success : msg = failed;
    cout << msg << endl;
    ++counter;
//test 3
    Mult(l->at(0), l->at(1)).Execute() == (33) ? msg = success : msg = failed;
    cout << msg << endl;
    ++counter;
//test 4
    Div(l->at(0), l->at(1)).Execute() == (5.5 / 6) ? msg = success : msg = failed;
    cout << msg << endl;
    ++counter;

    Number A(5);
    auto B = &A;




/*//test5
Mult(Number(5), Number(5));

Plus(Mult(l->at(3), l->at(4)), Mult(l->at(4), l->at(5)))) == (6062.06) ? msg = success : msg = failed;
cout << msg << endl;
++counter;

Plus(new Number(5), new Number(5));
Mult* A = new Mult(new Number(5), new Number(1));
Plus(A, new Number(5));*/

}

#define SIMSERVER_NUMBERTEST_H

#endif //SIMSERVER_NUMBERTEST_H
