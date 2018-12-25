//
// Created by stav on 12/25/18.
//

#ifndef SIMSERVER_LEXERTEST_H
#define SIMSERVER_LEXERTEST_H
using namespace std;
#include <vector>
#include <memory>
#include "string"
#include "../Lexer/Lexer.h"
class LexerTest{
private:
    int counter = 1;
    string success =  " passed";
    string failed =  " failed";
    string msg;
    int successCounter = 0;
    int failedCounter = 0;
    shared_ptr<Lexer> lexer= make_shared<Lexer>();
    vector<string> result;
    string input;

    //test 1
    input= "var x = 5";

};
#endif //SIMSERVER_LEXERTEST_H
