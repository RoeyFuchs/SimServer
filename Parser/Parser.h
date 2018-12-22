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
  shared_ptr<ShuntingYard> shuntingYard;
  shared_ptr<ConditionParser> currentConditionParse;
  shared_ptr<ExpressionMaps> expressionMaps;
  shared_ptr<ValidateExpression> validateExpression;
  vector<string> operators;
  map<string, int> expressionArguments;
  shared_ptr<Utils> utils;
  shared_ptr<Expression> ParseVar(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParseImplementation(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParseConnect(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParseOpenDataServer(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParsePrint(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParseSleep(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParseIf(std::vector<std::string> &tokens);
  shared_ptr<Expression> ParseWhile(std::vector<std::string> &tokens);
  shared_ptr<ConditionExpression> CreateCondition(std::vector<std::string> &tokens);

 public:
  Parser(shared_ptr<ExpressionMaps> expressionMaps) {
    expressionArguments.insert(std::pair<string, int>("openDataServer", 2));
    expressionArguments.insert(std::pair<string, int>("connect", 2));
    expressionArguments.insert(std::pair<string, int>("var", 1));
    expressionArguments.insert(std::pair<string, int>("while", 3));
    expressionArguments.insert(std::pair<string, int>("print", 1));
    expressionArguments.insert(std::pair<string, int>("sleep", 1));
    this->operators = {">", "<", "==", "!=", ">=", "<="};
    this->expressionMaps = expressionMaps;
    this->shuntingYard = make_shared<ShuntingYard>(this->expressionMaps);
    this->utils = make_shared<Utils>(this->operators, expressionMaps);
    this->validateExpression =
        make_shared<ValidateExpression>(this->operators, expressionMaps, this->expressionArguments);
  }
  void ParseLine(std::vector<std::string> &tokens);
  shared_ptr<Expression> MakeAnExpression(std::vector<std::string> &tokens);

};

#endif //SIMSERVER_PARSER_H