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
#include "../Expression/IfExpression.h"
#include "../Expression/WhileExpression.h"
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
    ConditionParser* currentConditionParse;
    std::map<std::string, VarExpression*>* varExpressionTable;
    Utils* utils;
    void ParseVar(std::vector<std::string> tokens);
    Expression* ParseConnect(std::vector<std::string> tokens);
    Expression* ParseOpenDataServer(std::vector<std::string> tokens);
    Expression* ParsePrint(std::vector<std::string> tokens);
    Expression* ParseSleep(std::vector<std::string> tokens);
    Expression* ParseIf(std::vector<std::string> tokens);
    Expression* ParseWhile(std::vector<std::string> tokens);
    ConditionExpression* CreateCondition(std::vector<std::string> tokens);
public:
    Parser(std::map<std::string, VarExpression*>* &varExpressionTable){
        this->varExpressionTable= varExpressionTable;
        this->shuntingYard= new ShuntingYard(this->varExpressionTable);
        this->utils= new Utils();
    }
    Expression* ParseLine(std::vector<std::string> tokens);

};


#endif //SIMSERVER_PARSER_H
