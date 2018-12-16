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
#include "../Expression/MathExpression/Modulo.h"
#include "../Expression/MathExpression/Neg.h"

#ifndef SIMSERVER_NUMBERTEST_H

using namespace std;

static void NumTest() {
    int counter = 1;

    string success =  " passed";
    string failed =  " failed";
    string msg;

    int successCounter = 0;
    int failCounter = 0;

    auto *l = new vector<Expression *>;
    l->push_back(new Number(5.5));  // 0
    l->push_back(new Number(6));  // 1
    l->push_back(new Number(9));  // 2
    l->push_back(new Number(150.2)); // 3
    l->push_back(new Number(39.3)); // 4
    l->push_back(new Number(-5.0)); // 5

//test 1
    Plus(l->at(0), l->at(1)).Execute() == (11.5) ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;
//test 2
    Minus(l->at(0), l->at(1)).Execute() == (-0.5) ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;
//test 3
    Mult(l->at(0), l->at(1)).Execute() == (33) ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;
//test 4
    Div(l->at(0), l->at(1)).Execute() == (5.5 / 6) ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;


//test5

    Plus(new Mult(l->at(2), l->at(3)), new Mult(l->at(3), l->at(4))).Execute() == (9+39.3)*150.2 ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;
    //test 6
    try {
        Div(new Number(5), new Number(0)).Execute();
        msg = failed;
        ++failCounter;
    } catch (exception e) {
        msg = success;
        ++successCounter;
    }
    cout << counter << msg << endl;
    ++counter;

    //test 7
    Div(new Number(5), new Modulo(new Number(22), new Number(5))).Execute() == 2.5 ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;

    //test 8
    Minus(new Neg(new Div(new Number(5), new Modulo(new Number(22), new Number(5)))), new Number(0)).Execute() == -2.5 ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;


    cout << "success: " << successCounter << " failed: " << failCounter <<endl;

}



#define SIMSERVER_NUMBERTEST_H

#endif //SIMSERVER_NUMBERTEST_H
