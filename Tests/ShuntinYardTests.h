//
// Created by roey on 12/15/18.
//

#ifndef SIMSERVER_SHUNTINYARDTESTS_H
#define SIMSERVER_SHUNTINYARDTESTS_H

#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <regex>
#include "string"
#include "../Expression/ShuntingYard.h"

using namespace std;
static void SYTest() {
    int counter = 1;

    string success =  " passed";
    string failed =  " failed";
    string msg;
    int successCounter = 0;
    int failedCounter = 0;

    auto mapp = new map<string, VarExpression*>;
    ShuntingYard *A = new ShuntingYard(mapp);
    auto vec = new vector<string>;

   //test 1
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("3");


    A->MakeExpression(*vec)->Execute() == 8 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();
//test 2
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("3");
    vec->emplace_back("*");
    vec->emplace_back("0");

    A->MakeExpression(*vec)->Execute() == 5 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();
//test 3
    vec->emplace_back("(");
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("3");
    vec->emplace_back(")");
    vec->emplace_back("*");
    vec->emplace_back("0");

    A->MakeExpression(*vec)->Execute() == 0 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();
//test 4
    vec->emplace_back("(");
    vec->emplace_back("(");
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("3");
    vec->emplace_back(")");
    vec->emplace_back("*");
    vec->emplace_back("0");
    vec->emplace_back(")");
    vec->emplace_back("+");
    vec->emplace_back("5");

    A->MakeExpression(*vec)->Execute() == 5 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 5
    vec->emplace_back("9");
    vec->emplace_back("-");
    vec->emplace_back("8");



    A->MakeExpression(*vec)->Execute() == 1 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 6
    vec->emplace_back("9");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("-");
    vec->emplace_back("1");


    A->MakeExpression(*vec)->Execute() == 0 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();


    //test 7
    vec->emplace_back("9");


    A->MakeExpression(*vec)->Execute() == 9 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 8
    vec->emplace_back("-");
    vec->emplace_back("6");


    A->MakeExpression(*vec)->Execute() == -6 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 9
    vec->emplace_back("-");
    vec->emplace_back("0");
    vec->emplace_back("-");
    vec->emplace_back("0");
    vec->emplace_back("-");
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("3");


    A->MakeExpression(*vec)->Execute() == -15 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 10
    vec->emplace_back("0");
    vec->emplace_back("-");
    vec->emplace_back("0");
    vec->emplace_back("-");
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("3");


    A->MakeExpression(*vec)->Execute() == -15 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 11
    vec->emplace_back("0");
    vec->emplace_back("-");
    vec->emplace_back("(");
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("3");
    vec->emplace_back(")");


    A->MakeExpression(*vec)->Execute() == 10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 12
    vec->emplace_back("(");
    vec->emplace_back("0");
    vec->emplace_back("-");
    vec->emplace_back("(");
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("3");
    vec->emplace_back(")");
    vec->emplace_back(")");


    A->MakeExpression(*vec)->Execute() == 10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 13
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("-");
    vec->emplace_back("8");



    A->MakeExpression(*vec)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 14
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("-");
    vec->emplace_back("8");



    A->MakeExpression(*vec)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 15
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("8");



    A->MakeExpression(*vec)->Execute() == 5 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 16
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("8");
    vec->emplace_back("-");
    vec->emplace_back("(");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back(")");



    A->MakeExpression(*vec)->Execute() == 13 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 17
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("8");
    vec->emplace_back("-");
    vec->emplace_back("(");
    vec->emplace_back("8");
    vec->emplace_back(")");



    A->MakeExpression(*vec)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 18
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("(");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back(")");



    A->MakeExpression(*vec)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 19
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("-");
    vec->emplace_back("2");




    A->MakeExpression(*vec)->Execute() == -10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 20
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("-");
    vec->emplace_back("(");
    vec->emplace_back("2");
    vec->emplace_back(")");




    A->MakeExpression(*vec)->Execute() == -10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 21
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("(");
    vec->emplace_back("-");
    vec->emplace_back("2");
    vec->emplace_back(")");




    A->MakeExpression(*vec)->Execute() == -10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 22
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("5");
    vec->emplace_back("/");
    vec->emplace_back("5");
    vec->emplace_back("*");
    vec->emplace_back("3");




    A->MakeExpression(*vec)->Execute() == (5*5/5*3) ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();




    cout << "success: " << successCounter << " failed: " << failedCounter <<endl;

}


#endif //SIMSERVER_SHUNTINYARDTESTS_H
