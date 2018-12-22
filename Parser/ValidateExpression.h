//
// Created by stav on 12/20/18.
//

#ifndef SIMSERVER_VALIDATEEXPRESSION_H
#define SIMSERVER_VALIDATEEXPRESSION_H

#include <vector>
#include <unordered_map>
#include "string"
#include <stdexcept>
#include <algorithm>
#include "../Expression/ConditionExpression.h"
#include "../Expression/VarExpression.h"
#include "../Expression/ExpressionMaps.h"

class ValidateExpression {
private:
    vector <string> operators;
    shared_ptr<ExpressionMaps> expressionMaps;
    unordered_map<string, int>expressionArguments;
public:
    ValidateExpression(vector <string> operators, shared_ptr<ExpressionMaps> expressionMaps,
                       unordered_map<string, int>expressionArguments){
        this->expressionMaps=expressionMaps;
        this->operators=operators;
        this->expressionArguments=expressionArguments;
    }
    void ValidateVarDefined(vector<string> &tokens);
    void ValidateOpenDataServer(vector<string> &tokens);
    void ValidateConnect(vector<string> &tokens);
    void ValidatePrint(vector<string> &tokens);

};


#endif //SIMSERVER_VALIDATEEXPRESSION_H