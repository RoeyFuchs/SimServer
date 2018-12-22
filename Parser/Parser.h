//
// Created by stav on 12/15/18.
//
#ifndef SIMSERVER_PARSER_H
#define SIMSERVER_PARSER_H

#include <vector>
#include "ValidateExpression.h"
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
    ExpressionMaps * expressionMaps;
    ValidateExpression * validateExpression;
    std::vector <std::string> operators;
    std::map<std::string, int>expressionArguments;
    Utils* utils;
    Expression* ParseVar(std::vector<std::string> &tokens);
    Expression* ParseImplementation(std::vector<std::string> &tokens);
    Expression* ParseConnect(std::vector<std::string> &tokens);
    Expression* ParseOpenDataServer(std::vector<std::string> &tokens);
    Expression* ParsePrint(std::vector<std::string> &tokens);
    Expression* ParseSleep(std::vector<std::string>& tokens);
    Expression* ParseIf(std::vector<std::string> &tokens);
    Expression* ParseWhile(std::vector<std::string> &tokens);
    ConditionExpression* CreateCondition(std::vector<std::string> &tokens);


public:
    Parser(ExpressionMaps* expressionMaps){
            expressionArguments.insert(std::pair<string, int>("openDataServer",2));
            expressionArguments.insert(std::pair<string, int>("connect",2));
            expressionArguments.insert(std::pair<string, int>("var",1));
            expressionArguments.insert(std::pair<string, int>("while",3));
            expressionArguments.insert(std::pair<string, int>("print",1));
            expressionArguments.insert(std::pair<string, int>("sleep",1));
            this->operators={">","<","==","!=",">=","<="};
            this->expressionMaps= expressionMaps;
            this->shuntingYard= new ShuntingYard(this->expressionMaps);
            this->utils= new Utils(this->operators,expressionMaps);
            this->validateExpression=new ValidateExpression(this->operators,expressionMaps,this->expressionArguments);
    }
    void ParseLine(std::vector<std::string> &tokens);
    Expression* MakeAnExpression(std::vector<std::string> &tokens);

};


#endif //SIMSERVER_PARSER_H