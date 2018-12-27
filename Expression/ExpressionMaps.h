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


using namespace std;
class ExpressionMaps {
  unordered_map<string, shared_ptr<VarExpression>> *nameExpressionMap;
  unordered_map<string, double> *bindValueMap;
  mutex locker;

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
    this->locker.lock();
    bool b = ((*this->nameExpressionMap).count(str) != 0);
    this->locker.unlock();
    return b;
  }
/**
 * get expression by the expression name
 * @param name - the name of the expression
 * @return smart pointer to the expressin
 */
  shared_ptr<VarExpression> GetExpressionByName(string name) {
    this->locker.lock();
    shared_ptr<VarExpression> temp = this->nameExpressionMap->at(name);
    this->locker.unlock();
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
    this->locker.lock();
    bool b = (map.count(key) > 0);
    this->locker.unlock();
    return b;
  }
/**
 * add a var expression to the map
 * @param name the name of the expression
 * @param exp a smart pointer to the var expression
 */
  void AddExpression(string name, shared_ptr<VarExpression> exp) {

    if (VarExists(name)) {
      this->locker.lock();
      this->nameExpressionMap->at(name) = exp;
      this->locker.unlock();
    } else {
      this->locker.lock();
      this->nameExpressionMap->insert(pair<string, shared_ptr<VarExpression>>(name, exp));
      this->locker.unlock();
    }

  }

/**
 * edit a vlue by bind
 * @param bind - the bind
 * @param val - the new value
 */
  void EditVal(string bind, double val) {
    this->locker.lock();
    this->bindValueMap->at(bind) = val;
    this->locker.unlock();
  }

  void UpdateExpression();

  void initializeMap();

  ~ExpressionMaps() {
    delete this->nameExpressionMap;
    delete this->bindValueMap;
  }

};

#endif //SIMSERVER_EXPRESSIONMAPS_H
