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

    ShuntingYard *A = new ShuntingYard();
    auto vec = new vector<string>;
    auto mapp = new map<string, VarExpression*>;
   //test 1
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("3");


    A->MakeExpression(*vec, *mapp)->Execute() == 8 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();
//test 2
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("3");
    vec->emplace_back("*");
    vec->emplace_back("0");

    A->MakeExpression(*vec, *mapp)->Execute() == 5 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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

    A->MakeExpression(*vec, *mapp)->Execute() == 0 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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

    A->MakeExpression(*vec, *mapp)->Execute() == 5 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 5
    vec->emplace_back("9");
    vec->emplace_back("-");
    vec->emplace_back("8");



    A->MakeExpression(*vec, *mapp)->Execute() == 1 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 6
    vec->emplace_back("9");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("-");
    vec->emplace_back("1");


    /* todo
     * The Bug here:
     * 9-8-1 equal to:
     * 9-(8-1) = 2
     * or
     * (9-8)-1 = 0
     */
    A->MakeExpression(*vec, *mapp)->Execute() == 0 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();


    //test 7
    vec->emplace_back("9");



    A->MakeExpression(*vec, *mapp)->Execute() == 9 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 8
    vec->emplace_back("-");
    vec->emplace_back("6");


    A->MakeExpression(*vec, *mapp)->Execute() == -6 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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


    A->MakeExpression(*vec, *mapp)->Execute() == -15 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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


    A->MakeExpression(*vec, *mapp)->Execute() == -15 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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


    A->MakeExpression(*vec, *mapp)->Execute() == 10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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


    A->MakeExpression(*vec, *mapp)->Execute() == 10 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 13
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("-");
    vec->emplace_back("8");



    A->MakeExpression(*vec, *mapp)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 14
    vec->emplace_back("5");
    vec->emplace_back("+");
    vec->emplace_back("-");
    vec->emplace_back("8");



    A->MakeExpression(*vec, *mapp)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 15
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("8");



    A->MakeExpression(*vec, *mapp)->Execute() == 5 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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



    A->MakeExpression(*vec, *mapp)->Execute() == 13 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
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



    A->MakeExpression(*vec, *mapp)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();

    //test 18
    vec->emplace_back("5");
    vec->emplace_back("-");
    vec->emplace_back("8");
    vec->emplace_back("+");
    vec->emplace_back("8");
    vec->emplace_back("-");
    vec->emplace_back("(");
    vec->emplace_back("8");
    vec->emplace_back(")");



    A->MakeExpression(*vec, *mapp)->Execute() == -3 ? (msg = success, ++successCounter) : (msg = failed, ++failedCounter);
    cout << counter << msg << endl;
    ++counter;
    vec->clear();



    cout << "success: " << successCounter << " failed: " << failedCounter <<endl;

}


#endif //SIMSERVER_SHUNTINYARDTESTS_H
