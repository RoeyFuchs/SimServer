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
    initializeMap();
  }

 /* check if var is exists
 * @param str  the name of the var
 * @return true or false
 */
  bool VarExists(string str) {
    return ((*this->nameExpressionMap).count(str) != 0);
  }
/**
 * get expression by the expression name
 * @param name - the name of the expression
 * @return smart pointer to the expressin
 */
  shared_ptr<VarExpression> GetExpressionByName(string name) {
    return this->nameExpressionMap->at(name);
  }
/**
 * get a value of bind
 * @param bind - the bind
 * @return the value
 */
  double GetValue(string bind) {
    return this->bindValueMap->at(bind);
  }
/**
 * check if the map include a key
 * @tparam T type of keys
 * @tparam S type of values
 * @param map the map
 * @param value the key to check
 * @return true or false
 */
  template<class T, class S>
  bool CheckMapHaveKey(unordered_map<T, S> map, T key) {
    return (map.count(key) > 0);
  }
/**
 * add a var expression to the map
 * @param name the name of the expression
 * @param exp a smart pointer to the var expression
 */
  void AddExpression(string name, shared_ptr<VarExpression> exp) {
    if (VarExists(name)) {
      this->nameExpressionMap->at(name) = exp;
    } else {
      this->nameExpressionMap->insert(pair<string, shared_ptr<VarExpression>>(name, exp));
    }
  }


/**
 * add value by bind
 * @param bind - the bind
 * @param val - the value
 */
  void AddValue(string bind, double val) {
    this->bindValueMap->insert(pair<string, double>(bind, val));
  }
/**
 * edit a vlue by bind
 * @param bind - the bind
 * @param val - the new value
 */
  void EditVal(string bind, double val) {
    this->bindValueMap->at(bind) = val;
  }

  void UpdateExpression();
/**
 * get the all vares in the map
 * @return a vector with smatrt pointers to the vars
 */
  vector<shared_ptr<VarExpression>> GetAllVars() {
    vector<shared_ptr<VarExpression>> vec;
    for (auto itr = this->nameExpressionMap->begin(); itr != this->nameExpressionMap->end(); ++itr) {
      vec.push_back((*itr).second);
    }
    return vec;
  }

  void initializeMap();

  ~ExpressionMaps() {
    delete this->nameExpressionMap;
    delete this->bindValueMap;
  }

};

#endif //SIMSERVER_EXPRESSIONMAPS_H
