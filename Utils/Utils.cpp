//
// Created by stav on 12/16/18.
//

#include <stdexcept>
#include <algorithm>
#include <regex>
#include "Utils.h"
/**
 * GetConditionOperatorPosition
 * @param tokens
 * @return index
 * The function search for operator condition position and return its index
 */
int Utils::GetConditionOperatorPosition(vector<string> &tokens) {
  for (int i = 0; i < tokens.size(); ++i) {
    for (int j = 0; j < operators.size(); ++j) {
      if (tokens[i] == operators[j]) {
        return i;
      }
    }
  }
  throw runtime_error("No condition operator found at condition command");
}
/**
 * GetPositionsOfExpressions
 * @param tokens
 * @return int vector with expression indexes
 */
vector<int> Utils::GetPositionsOfExpressions(vector<string> &tokens) {
  vector<int> expressionsPositions;
  //first element in vector is also an expression
  expressionsPositions.push_back(0);
  int isPreviousExpIsNumber = this->IsNumber(tokens[0]) || this->expressionMaps->VarExists(tokens[0]);
  for (int i = 1; i < tokens.size(); i++) {
    int isCurrentExpIsNumber = this->IsNumber(tokens[i]) || this->expressionMaps->VarExists(tokens[i]);
    //check for two consecutive numbers
    if (isCurrentExpIsNumber && isPreviousExpIsNumber) {
      expressionsPositions.push_back(i);
    }
    isPreviousExpIsNumber = isCurrentExpIsNumber;
  }
  return expressionsPositions;
}
/**
 * IsNumber
 * @param s
 * @return true if the string is a number or false otherwise
 */
bool Utils::IsNumber(const string &s) {
  return regex_match(s, regex("^(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
}

/**
* Slice
* @tparam T
* @param vec
* @param beginIndex
* @param endIndex
* @return sub vector according to given indexes
*/
vector<string> Utils::Slice(vector<string> myVec, int beginIndex, int endIndex) {
  vector<string> newVec;
  for (int i = beginIndex; i <= endIndex; ++i) {
    newVec.push_back(myVec[i]);
  }
  return newVec;

}
/**
 * the function create map between the number of the line and that value,
 * of the xml file
 * @return a map
 */
unordered_map<int, string> Utils::GetXmlOrder() {
  unordered_map<int, string> newMap;
  ifstream myFile(XML_ORDER_FILE);
  if (!myFile.is_open()) {
    throw runtime_error(string("can't open XML file"));
  }
  int i = 0;
  string line;
  while (getline(myFile, line)) {
    newMap[i] = line;
    ++i;
  }
  myFile.close();
  return newMap;
}

vector<string> Utils::SplitByChar(string &s, char delim) {
  vector<string> result;
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}

/**
 * delete char from char array
 * @param arr the array to delete from
 * @param size - the size of the array
 * @param charToDelete - the char to delete
 */
void Utils::DeleteChar(string& str, string& temp, int size, char charToDelete) {
  for (int i = 0; i < size; ++i) {
    if (str.at(i) == charToDelete) {
      temp = str.substr(i+1, str.length());
      str = str.substr(0, i-1);
      break;
    }
  }
}

