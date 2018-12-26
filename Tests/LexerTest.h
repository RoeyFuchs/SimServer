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
    input = "var a=bind \"a/a/a\"";
    output=lexer->SeparateLine(input);
    result={"var","a","=","bind","\"a/a/a\""};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 8
    counter++;
    input = "var a=bind b";
    output=lexer->SeparateLine(input);
    result={"var","a","=","bind","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 9
    counter++;
    input = "openDataServer 1+2+6*8 (6+4)";
    output=lexer->SeparateLine(input);
    result={"openDataServer", "1","+","2","+","6","*","8","(","6","+","4",")"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 10
    counter++;
    input = "print y";
    output=lexer->SeparateLine(input);
    result={"print","y"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 11
    counter++;
    input = "if a > b";
    output=lexer->SeparateLine(input);
    result={"if","a",">","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 12
    counter++;
    input = "print \"a/a/a\"";
    output=lexer->SeparateLine(input);
    result={"print","\"a/a/a\""};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 13
    counter++;
    input = "if a>b";
    output=lexer->SeparateLine(input);
    result={"if","a",">","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 14
    counter++;
    input = "if a<b";
    output=lexer->SeparateLine(input);
    result={"if","a","<","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 15
    counter++;
    input = "if a< b";
    output=lexer->SeparateLine(input);
    result={"if","a","<","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 16
    counter++;
    input = "if a <b";
    output=lexer->SeparateLine(input);
    result={"if","a","<","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 17
    counter++;
    input = "if a==b";
    output=lexer->SeparateLine(input);
    result={"if","a","==","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 18
    counter++;
    input = "if a != b";
    output=lexer->SeparateLine(input);
    result={"if","a","!=","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 19
    counter++;
    input = "if a!=b";
    output=lexer->SeparateLine(input);
    result={"if","a","!=","b"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 20
    counter++;
    input = "while abcd==b+ (bla/3)";
    output=lexer->SeparateLine(input);
    result={"while","abcd","==","b","+","(","bla","/","3",")"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 21
    counter++;
    input = "while abcd !=b+ (bdaba)";
    output=lexer->SeparateLine(input);
    result={"while","abcd","!=","b","+","(","bdaba",")"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 22
    counter++;
    input = "while abcd !=b+ (bdaba){";
    output=lexer->SeparateLine(input);
    result={"while","abcd","!=","b","+","(","bdaba",")","{"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 23
    counter++;
    input = "{";
    output=lexer->SeparateLine(input);
    result={"{"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 24
    counter++;
    input = "}";
    output=lexer->SeparateLine(input);
    result={"}"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 25
    counter++;
    input = "print y}";
    output=lexer->SeparateLine(input);
    result={"print","y","}"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 26
    counter++;
    input = "var x=5+8/(13+2)}";
    output=lexer->SeparateLine(input);
    result={"var","x","=","5","+","8","/","(","13","+","2",")","}"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 27
    counter++;
    input = "{var x=5+8/(13+2)}";
    output=lexer->SeparateLine(input);
    result={"{","var","x","=","5","+","8","/","(","13","+","2",")","}"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 28
    counter++;
    input = "var x= -5";
    output=lexer->SeparateLine(input);
    result={"var","x","=","-","5"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 29
    counter++;
    input = "var x= (-5)+3";
    output=lexer->SeparateLine(input);
    result={"var","x","=","(","-","5",")","+","3"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
    //test 30
    counter++;
    input = "connect 1.2.3.4.5 198";
    output=lexer->SeparateLine(input);
    result={"connect" ,"1.2.3.4.5","198"};
    if(output==result){
        successCounter++;
        cout<<"test:"<<counter<<success<<endl;
    }else{
        failedCounter++;
        cout<<"test:"<<counter<<failed<<endl;
    }
};
#endif //SIMSERVER_LEXERTEST_H