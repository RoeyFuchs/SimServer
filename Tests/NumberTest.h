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

    auto *l = new vector<shared_ptr<Expression>>;
    l->push_back(make_shared<Number>(5.5));  // 0
    l->push_back(make_shared<Number> (6));  // 1
    l->push_back(make_shared<Number>(9));  // 2
    l->push_back(make_shared<Number>(150.2)); // 3
    l->push_back(make_shared<Number>(39.3)); // 4
    l->push_back(make_shared<Number>(-5.0)); // 5

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

    Plus(make_shared<Mult>(l->at(2), l->at(3)), make_shared<Mult>(l->at(3), l->at(4))).Execute() == (9+39.3)*150.2 ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;
    //test 6
    try {
        Div(make_shared<Number>(5),make_shared<Number>(0)).Execute();
        msg = failed;
        ++failCounter;
    } catch (exception e) {
        msg = success;
        ++successCounter;
    }
    cout << counter << msg << endl;
    ++counter;

    //test 7
    Div(make_shared<Number>(5), make_shared<Modulo>(make_shared<Number>(22), make_shared<Number>(5))).Execute() == 2.5 ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;

    //test 8
    Minus(make_shared<Neg>(make_shared<Div>(make_shared<Number>(5), make_shared<Modulo>(make_shared<Number>(22), make_shared<Number>(5)))), make_shared<Number>(0)).Execute() == -2.5 ? (msg = success, ++successCounter) : (msg = failed, ++failCounter);
    cout << counter << msg << endl;
    ++counter;


    cout << "success: " << successCounter << " failed: " << failCounter <<endl;

}



#define SIMSERVER_NUMBERTEST_H

#endif //SIMSERVER_NUMBERTEST_H
