#ifndef SIMSERVER_EXPRESSIONMAPS_H
#define SIMSERVER_EXPRESSIONMAPS_H

#include <unordered_map>
#include <fstream>
#include "Expression.h"
#include "vector"
#include "VarExpression.h"
#include "Number.h"
#define XML_ORDER_FILE "XmlOrder.txt"

using namespace std;
class ExpressionMaps {
  unordered_map<string, shared_ptr<VarExpression>> *nameExpressionMap;
  unordered_map<string, double> *bindValueMap;
 public:
  ExpressionMaps() {
    this->nameExpressionMap = new unordered_map<string, shared_ptr<VarExpression>>;
    this->bindValueMap = new unordered_map<string, double>;
    //put the all value to zero
    InitilizeMap();
  }

  bool VarExists(string str) {
    return ((*this->nameExpressionMap).count(str) != 0);
  }

  shared_ptr<VarExpression> GetExpressionByName(string name) {
    return this->nameExpressionMap->at(name);
  }

  double GetValue(string bind) {
    return this->bindValueMap->at(bind);
  }

  void AddExpression(string name, shared_ptr<VarExpression> exp) {
    if (VarExists(name)) {
      this->nameExpressionMap->at(name) = exp;
    } else {
      this->nameExpressionMap->insert(pair<string, shared_ptr<VarExpression>>(name, exp));
    }
  }

  void AddValue(string bind, double val) {
    this->bindValueMap->insert(pair<string, double>(bind, val));
  }

  void EditVal(string bind, double val) {
    this->bindValueMap->at(bind) = val;
  }

  void UpdateExpression();

  vector<shared_ptr<VarExpression>> GetAllVars() {
    vector<shared_ptr<VarExpression>> vec;
    for (auto itr = this->nameExpressionMap->begin(); itr != this->nameExpressionMap->end(); ++itr) {
      vec.push_back((*itr).second);
    }
    return vec;
  }

  void InitilizeMap() {
    vector<string> vec;
    ifstream myFile(XML_ORDER_FILE);
    if(!myFile.is_open()) {
      throw runtime_error(string("can't open XML file"));
    }
    string line;
    while(getline(myFile, line)) {
      vec.push_back(line);
    }
    myFile.close();
    for(int i = 0; i < vec.size(); ++i) {
      bindValueMap->insert(pair<string, double>(vec.at(i), 0));
    }
  }

  ~ExpressionMaps() {
    delete this->nameExpressionMap;
    delete this->bindValueMap;
  }

};

#endif //SIMSERVER_EXPRESSIONMAPS_H
