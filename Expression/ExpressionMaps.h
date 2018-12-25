#ifndef SIMSERVER_EXPRESSIONMAPS_H
#define SIMSERVER_EXPRESSIONMAPS_H

#include <unordered_map>
#include <fstream>
#include "Expression.h"
#include "vector"
#include "VarExpression.h"
#include "Number.h"
#include <mutex>

#define XML_ORDER_FILE "XmlOrder.txt"
mutex locker;

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
    locker.lock();
    bool b = ((*this->nameExpressionMap).count(str) != 0);
    locker.unlock();
    return b;
  }
/**
 * get expression by the expression name
 * @param name - the name of the expression
 * @return smart pointer to the expressin
 */
  shared_ptr<VarExpression> GetExpressionByName(string name) {
    locker.lock();
    shared_ptr<VarExpression> temp = this->nameExpressionMap->at(name);
    locker.unlock();
    return temp;
  }
/**
 * get a value of bind
 * @param bind - the bind
 * @return the value
 */
  double GetValue(string bind) {
    locker.lock();
    double temp = this->bindValueMap->at(bind);
    locker.unlock();
    return temp;
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
    locker.lock();
    bool b = (map.count(key) > 0);
    locker.unlock();
    return b;
  }
/**
 * add a var expression to the map
 * @param name the name of the expression
 * @param exp a smart pointer to the var expression
 */
  void AddExpression(string name, shared_ptr<VarExpression> exp) {
    locker.lock();
    if (VarExists(name)) {
      this->nameExpressionMap->at(name) = exp;
    } else {
      this->nameExpressionMap->insert(pair<string, shared_ptr<VarExpression>>(name, exp));
    }
    locker.unlock();
  }



/**
 * add value by bind
 * @param bind - the bind
 * @param val - the value
 */
  void AddValue(string bind, double val) {
    locker.lock();
    this->bindValueMap->insert(pair<string, double>(bind, val));
    locker.unlock();
  }
/**
 * edit a vlue by bind
 * @param bind - the bind
 * @param val - the new value
 */
  void EditVal(string bind, double val) {
    locker.lock();
    this->bindValueMap->at(bind) = val;
    locker.unlock();
  }

  void UpdateExpression();
/**
 * get the all vares in the map
 * @return a vector with smatrt pointers to the vars
 */
  vector<shared_ptr<VarExpression>> GetAllVars() {
    locker.lock();
    vector<shared_ptr<VarExpression>> vec;
    for (auto itr = this->nameExpressionMap->begin(); itr != this->nameExpressionMap->end(); ++itr) {
      vec.push_back((*itr).second);
    }
    locker.unlock();
    return vec;
  }

  void initializeMap();

  ~ExpressionMaps() {
    delete this->nameExpressionMap;
    delete this->bindValueMap;
  }

};

#endif //SIMSERVER_EXPRESSIONMAPS_H
