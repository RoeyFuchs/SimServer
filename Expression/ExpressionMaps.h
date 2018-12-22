#ifndef SIMSERVER_EXPRESSIONMAPS_H
#define SIMSERVER_EXPRESSIONMAPS_H

#include "map"
#include "Expression.h"
#include "vector"
#include "VarExpression.h"
#include "Number.h"

using namespace std;
class ExpressionMaps {
map<string, VarExpression*>* nameExpressionMap;
map<string, double>* bindValueMap;
public:
ExpressionMaps() {
    this->nameExpressionMap = new map<string, VarExpression*>;
    this->bindValueMap = new map<string, double>;
}

bool VarExists(string str) {
  return ((*this->nameExpressionMap).count(str) != 0);
}

VarExpression* GetExpressionByName(string name) {
    return this->nameExpressionMap->at(name);
}

double GetValue(string bind) {
    return this->bindValueMap->at(bind);
}

void AddExpression(string name, VarExpression* exp) {
    this->nameExpressionMap->insert(pair<string, VarExpression*>(name, exp));
}

void AddValue(string bind, double val) {
    this->bindValueMap->insert(pair<string, double>(bind, val));
}

void EditVal(string bind, double val) {
    this->bindValueMap->at(bind) = val;
}

void UpdateExpression();

vector<VarExpression*> GetAllVars() {
    vector<VarExpression*> vec;
    for(auto itr = this->nameExpressionMap->begin(); itr != this->nameExpressionMap->end(); ++itr) {
        vec.push_back((*itr).second);
    }
    return vec;
}

~ExpressionMaps() {
    delete this->nameExpressionMap;
    delete this->bindValueMap;
}

};


#endif //SIMSERVER_EXPRESSIONMAPS_H
