//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_PARSER_H
#define SIMSERVER_PARSER_H

#include <vector>
#include <map>
#include "string"
#include "../Utils/Utils.h"
#include "../Expression/Expression.h"
#include "../Expression/ShuntingYard.h"
#include "../Expression/VarExpression.h"
#include "../Expression/Number.h"
#include "../Expression/ConnectExpression.h"
#include "../Expression/SleepExpression.h"
#include "../Expression/PrintExpression.h"
#include "../Expression/OpenDataServerExpression.h"
class Parser {
private:
    ShuntingYard* shuntingYard;
    Expression* currentExpression;
    Utils* utils;
    void ParseVar(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
    Expression* ParseConnect(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
    Expression* ParseOpenDataServer(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
    Expression* ParsePrint(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
    Expression* ParseSleep(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
public:
    Parser(){
        this->shuntingYard= new ShuntingYard();
        this->utils= new Utils();
    }
    Expression* ParseLine(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);

};


#endif //SIMSERVER_PARSER_H
