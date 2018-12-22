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
#include "../Expression/ExpressionMaps.h"

class ValidateExpression {
private:
    std::vector <std::string> operators;
    ExpressionMaps* expressionMaps;
    std::map<std::string, int>expressionArguments;
public:
    ValidateExpression(std::vector <std::string> operators, ExpressionMaps* expressionMaps,
                       std::map<std::string, int>expressionArguments){
        this->expressionMaps=expressionMaps;
        this->operators=operators;
        this->expressionArguments=expressionArguments;
    }
    void ValidateVarDefined(std::vector<std::string> &tokens);
    void ValidateOpenDataServer(std::vector<std::string> &tokens);
    void ValidateConnect(std::vector<std::string> &tokens);
    void ValidatePrint(std::vector<std::string> &tokens);

};


#endif //SIMSERVER_VALIDATEEXPRESSION_H