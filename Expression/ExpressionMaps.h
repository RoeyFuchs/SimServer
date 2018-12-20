#ifndef SIMSERVER_EXPRESSIONMAPS_H
#define SIMSERVER_EXPRESSIONMAPS_H

#include "map"
#include "Expression.h"

using namespace std;
class ExpressionMaps {
map<string, Expression*>* nameExpressionMap;
map<string, double>* bindValueMap;
public:
ExpressionMaps() {
    this->nameExpressionMap = new map<string, Expression*>;
    this->bindValueMap = new map<string, double>;
}

Expression* GetExpressionByName(string name) {
    return this->nameExpressionMap->at(name);
}

double GetValue(string bind) {
    return this->bindValueMap->at(bind);
}

void AddExpression(string name, Expression* exp) {
    this->nameExpressionMap->insert(pair<string, Expression*>(name, exp));
}

void AddValue(string bind, double val) {
    this->bindValueMap->insert(pair<string, double>(bind, val));
}

void EditVal(string bind, double val) {
    this->bindValueMap->at(bind) = val;
}

~ExpressionMaps() {
    delete this->nameExpressionMap;
    delete this->bindValueMap;
}

};


#endif //SIMSERVER_EXPRESSIONMAPS_H
