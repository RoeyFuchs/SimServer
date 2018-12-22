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
#include <unordered_map>
#include <string>
#include <regex>
#include <fstream>
class Utils {
private:
    vector <string> operators;
    shared_ptr<ExpressionMaps> expressionMaps;
public:
    Utils(vector <string> operators,shared_ptr<ExpressionMaps> expressionMaps){
        this->expressionMaps=expressionMaps;
        this->operators=operators;
    }
    vector<string> Slice (vector<string> vec, int beginIndex, int endIndex);

    int GetConditionOperatorPosition(vector<string> &tokens);

     vector<int> GetPositionsOfExpressions(vector<string> &tokens);

    bool IsNumber(const string& s);

    static unordered_map<int, string> GetXmlOrder();


    static vector<string> SplitByChar(string &s, char delim);
    static string SubStringUntilChar(string &str, char ch);
  static string SubStringFromChar(string &str, char ch);
};

#endif //SIMSERVER_UTILS_H