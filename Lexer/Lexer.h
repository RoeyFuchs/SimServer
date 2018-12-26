//
// Created by stav on 12/25/18.
//

#ifndef SIMSERVER_LEXER_H
#define SIMSERVER_LEXER_H
using namespace std;
#include <vector>
#include <memory>
#include "string"
#include "../Parser/Parser.h"

class Lexer {
private:
    vector<char > conditionOperators;
    bool IsConditionOperator(char c);
    bool IsMathOperators(char c);
    vector <char > mathOperators;
    string SeparateLineByComma(string line);
    vector<string> ConvertStringToVector(string line);
    shared_ptr<Parser> prsr;

public:
    Lexer(shared_ptr<Parser> prsr){
        this->mathOperators={'+','-','*','/','%','(',')','{','}'};
       this->conditionOperators=  {'>','<','=','!'};
       this->prsr = prsr;
    }
    void SeparateLine(string line);

};


#endif //SIMSERVER_LEXER_H
