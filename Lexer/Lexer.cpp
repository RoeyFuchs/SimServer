//
// Created by stav on 12/25/18.
//

#include <sstream>
#include "Lexer.h"

/**
 * IsConditionOperator
 * @return true if current string is condition operator or false otherwise
 */
bool Lexer::IsConditionOperator(char c) {
  for (int j = 0; j < conditionOperators.size(); ++j) {
    if (c == conditionOperators[j]) {
      return true;
    }
  }
  return false;
}
/**
 * IsMathOperators
 * @return true if current string is math operator or false otherwise
 */
bool Lexer::IsMathOperators(char c) {
  for (int j = 0; j < mathOperators.size(); ++j) {
    if (c == mathOperators[j]) {
      return true;
    }
  }
  return false;
}
/**
 * SeparateLineByComma
 * @param line
 * @return seperate line by comma char
 */
string Lexer::SeparateLineByComma(string line) {
  string concatString;
  char space = ' ';
  int i = 0;
  int len = line.size();
  while (i < len) {
      //if line string contains quotation mark
    if (line[i] == '\"') {
      string str;
      str += line[i];
      i++;
      //copy all phrase
      while (line[i] != '\"') {
        str += line[i];
        i++;
      }
      str += line[i];
      concatString += str;
      concatString += ",";
    } else if ((line[i] == space && !concatString.empty())) {
        //separate spaces
      concatString += ",";
    } else if (this->IsMathOperators(line[i]) ||
        (line[i] == '=' && !IsConditionOperator(line[i + 1]) &&
            !IsConditionOperator(concatString[concatString.length() - 1]))) {
        //separate =,math operators
      concatString += ",";
      concatString += line[i];
      concatString += ",";
    } else if (i < len && IsConditionOperator(line[i]) && IsConditionOperator(line[i + 1])) {
        //separate condition operators
      concatString += ",";
      concatString += line[i];
      i++;
      concatString += line[i];
      concatString += ",";
    } else if (IsConditionOperator(line[i])) {
        //separate condition operator
      concatString += ",";
      concatString += line[i];
      concatString += ",";
    } else if (line[i] != space) {
        //copy char
      concatString += line[i];
    }
    i++;
  }
  return concatString;
}
/**
 * ConvertStringToVector
 * @param line
 * @return vector of separated string
 */
vector<string> Lexer::ConvertStringToVector(string line) {
  vector<string> vec;
  int k = 0;
  while (k < line.size()) {
    string str;
    while (line[k] != ',' && k < line.size()) {
      str += line[k];
      k++;
    }
    if (str.length() > 0) {
      vec.push_back(str);
    }
    k++;

  }
  return vec;
}
/**
 * SeparateLine
 * @param line
 * @return vector of strings
 * The function separate line according to known operators and spaces
 */
void Lexer::SeparateLine(string line) {
  string seperatedLine = this->SeparateLineByComma(line);
  vector<string> vec = ConvertStringToVector(seperatedLine);
  this->prsr->ParseLine(vec);

}