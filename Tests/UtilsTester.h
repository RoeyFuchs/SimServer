//
// Created by stav on 12/19/18.
//

#ifndef SIMSERVER_UTILSTESTER_H
#define SIMSERVER_UTILSTESTER_H
#include <vector>
#include <map>
#include <iostream>
#include "string"
#include "../Utils/Utils.h"

    void PrintResult(int testNum ,bool result){
        if(result){
            std::cout<<"test:"<<testNum<<" ->"<<"passed";
        }else{
            std::cout<<"test:"<<testNum<<" ->"<<"failed";
        }
    }
    void UtilsTest(){
     /*   std::vector <std::string>  operators={">","<","==","!=",">=","<="};
        Utils *utilsTest= new Utils(operators);
        std::vector <std::string> tokens;

        //test1
        tokens.push_back("1");
        tokens.push_back("+");
        tokens.push_back("2");
        tokens.push_back("1");
        std::vector<int> indexes= utilsTest->GetPositionsOfExpressions(tokens);
        if(indexes[0]==0&& indexes[1]==3){
            PrintResult(1, 1);
        }else{
            PrintResult(1, 0);
        }*/

    }

#endif //SIMSERVER_UTILSTESTER_H
