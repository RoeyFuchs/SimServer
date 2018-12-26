//
// Created by stav on 12/17/18.
//

#ifndef SIMSERVER_PARSERTESTS_H
#define SIMSERVER_PARSERTESTS_H
#include <vector>
#include <unordered_map>
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
    shared_ptr<ExpressionMaps> expressionMaps=make_shared<ExpressionMaps>();
    shared_ptr<Number> num=make_shared<Number>(5);
    shared_ptr<VarExpression> roll=make_shared<VarExpression>("/a/b/c");
    roll->SetExpression(num);
    shared_ptr<VarExpression> elevator=make_shared<VarExpression>("/d/e/f");
    expressionMaps->AddExpression("roll",roll);
    expressionMaps->AddExpression("elevator",elevator);
    vector<string> operators={">", "<", "==", "!=", ">=", "<="};;
    shared_ptr<Parser> parser= make_shared<Parser>(expressionMaps,operators);
    int countTest=0;

    //test 1
    countTest++;
    vector<string>* vec = new vector<string>{"var","a","=","bind","\"a/a/a\""};
    parser->ParseLine(*vec);
    shared_ptr<VarExpression> newVarA=expressionMaps->GetExpressionByName("a");
    if(newVarA!= nullptr && newVarA->GetPath()=="a/a/a"){
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
    shared_ptr<VarExpression> newVarB=expressionMaps->GetExpressionByName("b");
    if(newVarB!= nullptr && newVarB->GetPath()=="a/a/a"){
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
    shared_ptr<VarExpression> newVar=expressionMaps->GetExpressionByName("k");
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
    shared_ptr<Expression> expr= parser->MakeAnExpression(*vec);
    shared_ptr<OpenDataServerExpression> openDataServerExpression=
            dynamic_pointer_cast<OpenDataServerExpression>(expr);
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
    openDataServerExpression=
            dynamic_pointer_cast<OpenDataServerExpression>(expr);
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
    //test 13
    countTest++;
    vec = new vector<string>{"connect","a"};
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
    //test 14
    countTest++;
    vec = new vector<string>{"connect","a","b","c"};
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
    //test 15
    countTest++;
    vec = new vector<string>{"connect","1.2.3","50","+","3"};
    isExp=0;
    expr= parser->MakeAnExpression(*vec);
    shared_ptr<ConnectExpression> connectExp=dynamic_pointer_cast<ConnectExpression>(expr);
    if(connectExp!= nullptr && connectExp->GetPort()->Execute()==53
       && connectExp->GetIp()=="1.2.3"){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 16
    countTest++;
    vec = new vector<string>{"print","1.2.3","50","+","3"};
    isExp=0;
    shared_ptr<PrintExpression> printExpression;
    try {
        expr= parser->MakeAnExpression(*vec);
        printExpression=dynamic_pointer_cast<PrintExpression>(expr);
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
    //test 17
    countTest++;
    vec = new vector<string>{"print"};
    isExp=0;
    try {
        expr= parser->MakeAnExpression(*vec);
        printExpression=dynamic_pointer_cast<PrintExpression>(expr);
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

    //test 18
    countTest++;
    vec = new vector<string>{"print","18 passed"};
    isExp=0;
    parser->MakeAnExpression(*vec)->Execute();

    //test 23
    countTest++;
    vec = new vector<string>{"sleep","51","-","10"};
    isExp=0;
    expr= parser->MakeAnExpression(*vec);
    shared_ptr<SleepExpression> sleepExp=dynamic_pointer_cast<SleepExpression>(expr);
    if( sleepExp->GetSleepingTimeExpression()->Execute()==41){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }


    //test 24
    countTest++;
    vec = new vector<string>{"a","=","bind","\"a/a/g\""};
    parser->ParseLine(*vec);
    newVarA=expressionMaps->GetExpressionByName("a");
    if(newVarA!= nullptr && newVarA->GetPath()=="a/a/g"){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 25
    countTest++;
    vec = new vector<string>{"b","=","bind","a"};
    parser->ParseLine(*vec);
    newVarB=expressionMaps->GetExpressionByName("b");
    if(newVarB!= nullptr && newVarB->GetPath()=="a/a/g"){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }


    //test 29
    countTest++;
    vec = new vector<string>{"k","=","roll"};
    parser->ParseLine(*vec);
    newVar=expressionMaps->GetExpressionByName("k");
    if(newVar!= nullptr && newVar->GetExpression()->Execute()==5){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 30
    countTest++;
    vec = new vector<string>{"b","=","bind","op"};
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
    //test 31
    countTest++;
    vec = new vector<string>{"b","=","op"};
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
    //test 32
    countTest++;
    vec = new vector<string>{"sleep","51"};
    isExp=0;
    expr= parser->MakeAnExpression(*vec);
    sleepExp=dynamic_pointer_cast<SleepExpression>(expr);
    if(sleepExp->GetSleepingTimeExpression()->Execute()==51){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 33
    countTest++;
    vec = new vector<string>{"if","5","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","acg","=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","agk","=","9","*","4"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    double A=expressionMaps->GetExpressionByName("acg")->Execute();
    double  B=expressionMaps->GetExpressionByName("agk")->Execute();
    if(A==5
       &&B==36){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 34
    countTest++;
    vec = new vector<string>{"if","5","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","aa","=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","ab","=","9","*","4"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("aa")->Execute();
    B=expressionMaps->GetExpressionByName("ab")->Execute();
    if(A==5
       &&B==36){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 35
    countTest++;
    vec = new vector<string>{"if","5","!=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"roll""=","6"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("roll")->Execute();
    if(A==5){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 36-4
    countTest++;
    vec = new vector<string>{"if","5","==","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","aaa","=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","aba","=","9","*","4"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("aaa")->Execute();
    B=expressionMaps->GetExpressionByName("aba")->Execute();
    if(A==5
       &&B==36){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 33
    countTest++;
    // vector<string>* vec;
    vec = new vector<string>{"if","5","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","aaq","=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","10","/","2","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","acq","=","80"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","abq","=","9","*","4"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("aaq")->Execute();
    B=expressionMaps->GetExpressionByName("abq")->Execute();
    double C=expressionMaps->GetExpressionByName("acq")->Execute();
    if(A==5
       &&B==36&&C==80){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 34
    countTest++;
    vec = new vector<string>{"var","t","=","36"};
    parser->ParseLine(*vec);
    //   vec = new vector<string>{"while","abyq","<","32","{"};
    //  parser->ParseLine(*vec);
    vec = new vector<string>{"t","=","t","-","9"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("t")->Execute();
    if(A==27){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 35
    countTest++;
    vec = new vector<string>{"var","abyq","=","36"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"while","abyq",">","32","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"abyq","=","abyq","-","1"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("abyq")->Execute();
    if(A==32){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 36
    countTest++;
    vec = new vector<string>{"while","16",">","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"roll","=","roll","+","1"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","16","/","2","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","eight","=","8"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("roll")->Execute();
    B=expressionMaps->GetExpressionByName("eight")->Execute();
    if(A==16
       &&B==8){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
//test 37
    countTest++;
    vec = new vector<string>{"while","16",">","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"roll","=","roll","+","1"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","29","/","2","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","eight","=","8"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("roll")->Execute();
    B=expressionMaps->GetExpressionByName("eight")->Execute();
    if(A==16
       &&B==8){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }

//test 38
    countTest++;
    // vector<string>* vec;
    vec = new vector<string>{"roll","=","9"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","9","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","aaq","=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","19","-","10","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","acq","=","80"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","4","+","5","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","agq","=","81"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","abq","=","9","*","4"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("aaq")->Execute();
    B=expressionMaps->GetExpressionByName("acq")->Execute();
    C=expressionMaps->GetExpressionByName("agq")->Execute();
    if(A==9
       &&B==80&&C==81){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }

//test 39
    countTest++;
    // vector<string>* vec;
    vec = new vector<string>{"if","9","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","taaq","=","roll"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","19","-","11","==","3","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"taaq","=","88"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","4","+","5","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"taaq","=","89"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","tabq","=","9","*","10"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("taaq")->Execute();
    double D=expressionMaps->GetExpressionByName("tabq")->Execute();
    if(A==9&& D==90){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 40
    countTest++;
    vec = new vector<string>{"var","ad","=","36"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","ad","<","32","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"ad","=","70","-","9"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("ad")->Execute();
    if(A==36){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 40
    countTest++;
    vec = new vector<string>{"var","ad","=","36"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"ad","=","70","-","9"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("ad")->Execute();
    if(A==61){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 40
    countTest++;
    vec = new vector<string>{"var","ad","=","36"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"ad","=","79","-","roll"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("ad")->Execute();
    if(A==70){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 40
    countTest++;
    vec = new vector<string>{"var","ad","=","36"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"ad","=","136","-","ad"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("ad")->Execute();
    if(A==100){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 40
    countTest++;
    vec = new vector<string>{"var","abyq","=","10"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"var","ad","=","36"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"ad","=","136","-","ad","-","abyq"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("ad")->Execute();
    if(A==90){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 37
    countTest++;
    vec = new vector<string>{"while","160",">","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"roll","=","roll","+","1"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"if","-","2","==","roll","{"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"eight","=","18"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    vec = new vector<string>{"}"};
    parser->ParseLine(*vec);
    A=expressionMaps->GetExpressionByName("roll")->Execute();
    B=expressionMaps->GetExpressionByName("eight")->Execute();
    if(A==160
       &&B==8){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }

    //test 43
    countTest++;
    vec = new vector<string>{"openDataServer","(","50",")","8","/","2"};
    isExp=0;
    expr= parser->MakeAnExpression(*vec);
    openDataServerExpression=
            dynamic_pointer_cast<OpenDataServerExpression>(expr);
    if(openDataServerExpression!= nullptr && openDataServerExpression->GetPort()->Execute()==50
       && openDataServerExpression->GetSamplingRate()->Execute()==4){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }

    //test 44
    countTest++;
    vec = new vector<string>{"openDataServer","(","50",")","(","8","/","2",")"};
    isExp=0;
    expr= parser->MakeAnExpression(*vec);
    openDataServerExpression=
            dynamic_pointer_cast<OpenDataServerExpression>(expr);
    if(openDataServerExpression!= nullptr && openDataServerExpression->GetPort()->Execute()==50
       && openDataServerExpression->GetSamplingRate()->Execute()==4){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
    //test 44
    countTest++;
    vec = new vector<string>{"openDataServer","(","50",")","2","+","(","4","/","2",")"};
    isExp=0;
    expr= parser->MakeAnExpression(*vec);
    openDataServerExpression=
            dynamic_pointer_cast<OpenDataServerExpression>(expr);
    if(openDataServerExpression!= nullptr && openDataServerExpression->GetPort()->Execute()==50
       && openDataServerExpression->GetSamplingRate()->Execute()==4){
        cout<<countTest<<success<<endl;
        successCounter++;
    }else{
        cout<<countTest<<failed<<endl;
        failedCounter++;
    }
}

#endif //SIMSERVER_PARSERTESTS_H