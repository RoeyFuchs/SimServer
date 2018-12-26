//
// Created by stav on 12/25/18.
//

#ifndef SIMSERVER_LEXERTEST_H
#define SIMSERVER_LEXERTEST_H
using namespace std;
#include <vector>
#include <memory>
#include <iostream>
#include "string"
#include "../Lexer/Lexer.h"

static void RunLexerTests(){
    int counter = 0;
    string success =  " passed";
    string failed =  " failed";
    string msg;
    int successCounter = 0;
    int failedCounter = 0;
    shared_ptr<Lexer> lexer= make_shared<Lexer>();
    vector<string> output;
    vector<string> result;
    string input;
    //test 1
    counter++;
    input = "var x = 5";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }

    //test 2
    counter++;
    input = "var x = 5 + 8 / 13";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","8","/","13"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 3
    counter++;
    input = "var x = 5 + 8 / ( 13 + 2 )";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","8","/","(","13","+","2",")"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }

    //test 4
    counter++;
    input = "var x = 5+2";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","2"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 5
    counter++;
    input = "var x=5+2";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","2"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }

    //test 6
    counter++;
    input = "var x=5+8/(13+2)";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","8","/","(","13","+","2",")"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 7
    counter++;
 //   input = "var x=bind "a/b/a"";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","8","/","(","13","+","2",")"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }

};
#endif //SIMSERVER_LEXERTEST_H