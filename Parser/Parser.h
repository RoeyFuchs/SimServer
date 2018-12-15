//
// Created by stav on 12/15/18.
//

#ifndef SIMSERVER_PARSER_H
#define SIMSERVER_PARSER_H

#include <vector>
#include <map>
#include "string"
#include "../Expression/Expression.h"
#include "../Expression/VarExpression.h"
#include "../Expression/OpenDataServerExpression.h"
class Parser {
    Expression ParseLine(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
    void ParseVar(std::vector<std::string> tokens,std::map<std::string, VarExpression*> &varExpressionTable);
    Expression* ParseConnectDataServer(std::vector<std::string> tokens);
};


#endif //SIMSERVER_PARSER_H
