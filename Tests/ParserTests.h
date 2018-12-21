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
static void RunParserTests(){
        int counter = 1;

        string success =  " passed";
        string failed =  " failed";
        string msg;
        int successCounter = 0;
        int failedCounter = 0;
        std::map<std::string, VarExpression*>* varsMap=new std::map<std::string, VarExpression*>();
        Number* num=new Number(5);
        VarExpression* roll=new VarExpression("/a/b/c");
        roll->SetExpression(num);
        VarExpression* elevator=new VarExpression("/d/e/f");
        ( *varsMap)["roll"]=roll;
        ( *varsMap)["elevator"]=elevator;
        Parser* parser= new Parser(varsMap);
        int countTest=0;

        //test 1
        countTest++;
        vector<string>* vec = new vector<string>{"var","a","=","bind","\"a/a/a\""};
        parser->ParseLine(*vec);
        VarExpression* newVarA=(*varsMap)["a"];
        if(newVarA!= nullptr && newVarA->GetPath()=="\"a/a/a\""){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
        //test 2
        countTest++;
        vec = new vector<string>{"var","b","=","bind","a"};
        parser->ParseLine(*vec);
        VarExpression* newVarB=(*varsMap)["b"];
        if(newVarB!= nullptr && newVarB->GetPath()=="\"a/a/a\""){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
        //test 3
        countTest++;
        vec = new vector<string>{"var","b","bind","a"};
        int isExp=0;
        try {
                parser->ParseLine(*vec);
        }catch (exception e){
                isExp=1;
        }
        if(isExp){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }

        //test 4
        countTest++;
        vec = new vector<string>{"var","b","=","bind"};
        isExp=0;
        try {
                parser->ParseLine(*vec);
        }catch (exception e){
                isExp=1;
        }
        if(isExp){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }

        //test 5
        countTest++;
        vec = new vector<string>{"var","b","bind","a"};
        isExp=0;
        try {
                parser->ParseLine(*vec);
        }catch (exception e){
                isExp=1;
        }
        if(isExp){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
        //test 6
        countTest++;
        vec = new vector<string>{"var","k","=","roll"};
        parser->ParseLine(*vec);
        VarExpression* newVar=(*varsMap)["k"];
        if(newVar!= nullptr && newVar->GetExpression()->Execute()==5){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
        //test 7
        countTest++;
        vec = new vector<string>{"var","b","=","bind","op"};
        isExp=0;
        try {
                parser->ParseLine(*vec);
        }catch (exception e){
                isExp=1;
        }
        if(isExp){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
        //test 8
        countTest++;
        vec = new vector<string>{"var","b","=","op"};
        isExp=0;
        try {
                parser->ParseLine(*vec);
        }catch (exception e){
                isExp=1;
        }
        if(isExp){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
    //test 9
    countTest++;
    vec = new vector<string>{"openDataServer"};
    isExp=0;
    try {
        parser->ParseLine(*vec);
    }catch (exception e){
        isExp=1;
    }
    if(isExp){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 10
    countTest++;
    vec = new vector<string>{"openDataServer","50","8","/","2"};
     isExp=0;
        Expression* expr= parser->MakeAnExpression(*vec);
        OpenDataServerExpression* openDataServerExpression=(OpenDataServerExpression*)expr;
        if(openDataServerExpression!= nullptr && openDataServerExpression->GetPort()->Execute()==50
        && openDataServerExpression->GetSamplingRate()->Execute()==4){
            cout<<countTest<<success<<endl;
            successCounter++;
        }else{
            cout<<countTest<<failed<<endl;
            failedCounter++;
        }
        //test 11
        countTest++;
        vec = new vector<string>{"openDataServer","50","+","3","8"};
        isExp=0;
         expr= parser->MakeAnExpression(*vec);
         openDataServerExpression=(OpenDataServerExpression*)expr;
        if(openDataServerExpression!= nullptr && openDataServerExpression->GetPort()->Execute()==53
           && openDataServerExpression->GetSamplingRate()->Execute()==8){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
        //test 12
        countTest++;
        vec = new vector<string>{"openDataServer","a"};
        isExp=0;
        try {
                parser->ParseLine(*vec);
        }catch (exception e){
                isExp=1;
        }
        if(isExp){
                cout<<countTest<<success<<endl;
                successCounter++;
        }else{
                cout<<countTest<<failed<<endl;
                failedCounter++;
        }
}
#endif //SIMSERVER_PARSERTESTS_H