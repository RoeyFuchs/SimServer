//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_UTILS_H
#define SIMSERVER_UTILS_H

#include "../Expression/ConditionExpression.h"
#include "../Expression/VarExpression.h"
#include <vector>
#include <map>
#include <string>
#include <regex>
class Utils {
private:
    std::vector <std::string> operators;
    std::map<std::string, VarExpression*>* varExpressionTable;
public:
    Utils(std::vector <std::string> operators, std::map<std::string, VarExpression*>* &varExpressionTable){
        this->varExpressionTable=varExpressionTable;
        this->operators=operators;
    }
    std::vector<std::string> Slice (std::vector<std::string> vec, int beginIndex, int endIndex);

    int GetConditionOperatorPosition(std::vector<std::string> &tokens);

     std::vector<int> GetPositionsOfExpressions(std::vector<std::string> &tokens);

    bool IsNumber(const std::string& s);

    bool IsVar(const std::string& s);
};

#endif //SIMSERVER_UTILS_H