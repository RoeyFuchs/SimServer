//
// Created by stav on 12/25/18.
//

#ifndef SIMSERVER_LEXER_H
#define SIMSERVER_LEXER_H
using namespace std;
#include <vector>
#include "string"


class Lexer {
private:
    vector<char > conditionOperators;
    bool IsConditionOperator(char c);
    bool IsMathOperators(char c);
    vector <char > mathOperators;
    string SeparateLineByComma(string line);
    vector<string> ConvertStringToVector(string line);

public:
    Lexer(){
        this->mathOperators={'+','-','*','/','%','(',')','{','}'};
       this->conditionOperators=  {'>','<','=','!'};
    }
    vector<string> SeparateLine(string line);

};


#endif //SIMSERVER_LEXER_H
