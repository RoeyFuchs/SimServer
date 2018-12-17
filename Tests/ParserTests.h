//
// Created by stav on 12/17/18.
//

#ifndef SIMSERVER_PARSERTESTS_H
#define SIMSERVER_PARSERTESTS_H
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <regex>
#include "string"
#include "../Parser/Parser.h"
class ParserTest{
    static void RunParserTests(){
        int counter = 1;

        string success =  " passed";
        string failed =  " failed";
        string msg;
        int successCounter = 0;
        int failedCounter = 0;
        auto mapp = new map<string, VarExpression*>;
        Parser* parser= new Parser(mapp);
        vector<string>* vec = new vector<string>;

        //test 1
        vec->emplace_back("print");
        vec->emplace_back("Hello");
        parser->ParseLine(vec);
    }
};
#endif //SIMSERVER_PARSERTESTS_H
