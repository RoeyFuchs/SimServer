//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_UTILS_H
#define SIMSERVER_UTILS_H

#define XML_ORDER_FILE "XmlOrder.txt"

#include "../Expression/ConditionExpression.h"
#include "../Expression/VarExpression.h"
#include "../Expression/ExpressionMaps.h"
#include <vector>
#include <map>
#include <string>
#include <regex>
#include <fstream>
class Utils {
private:
    std::vector <std::string> operators;
    ExpressionMaps* expressionMaps;
public:
    Utils(std::vector <std::string> operators, ExpressionMaps *expressionMaps){
        this->expressionMaps=expressionMaps;
        this->operators=operators;
    }
    std::vector<std::string> Slice (std::vector<std::string> vec, int beginIndex, int endIndex);

    int GetConditionOperatorPosition(std::vector<std::string> &tokens);

     std::vector<int> GetPositionsOfExpressions(std::vector<std::string> &tokens);

    bool IsNumber(const std::string& s);

    static std::map<int, std::string> GetXmlOrder();

    static std::vector<std::string> SplitByChar(char *phrase, std::string delimiter);
};

#endif //SIMSERVER_UTILS_H