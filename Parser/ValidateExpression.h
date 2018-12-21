//
// Created by stav on 12/20/18.
//

#ifndef SIMSERVER_VALIDATEEXPRESSION_H
#define SIMSERVER_VALIDATEEXPRESSION_H

#include <vector>
#include <map>
#include "string"
#include <stdexcept>
#include <algorithm>
#include "../Expression/ConditionExpression.h"
#include "../Expression/VarExpression.h"

class ValidateExpression {
private:
    std::vector <std::string> operators;
    std::map<std::string, VarExpression*>* varExpressionTable;
public:
    ValidateExpression(std::vector <std::string> operators, std::map<std::string, VarExpression*>* &varExpressionTable){
        this->varExpressionTable=varExpressionTable;
        this->operators=operators;
    }
    void ValidateVarDefined(std::vector<std::string> &tokens);
    void ValidateOpenDataServer(std::vector<std::string> &tokens);


};


#endif //SIMSERVER_VALIDATEEXPRESSION_H