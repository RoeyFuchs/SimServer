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
 * SeparateLine
 * @param line
 * @return vector of strings
 * The function separate line according to known operators and spaces
 */
vector<string> Lexer::SeparateLine(string line) {
    string subStr;
    vector<string> vec;
    char space =' ';
    int i=0;
    for(int i=0; i<line.size();i++){
        if(line[i]=='='&& !IsConditionOperator(line[i+1])&& !IsConditionOperator(subStr[subStr.length()-1])){
            subStr+=",";
        } else if(line[i]!= space){
            subStr+=line[i];
        }else if(line[i]==space&&(this->IsMathOperators(line[i-1]))&&(this->IsMathOperators(line[i+1]))){
            continue;
        }else if(line[i]==space&& !subStr.empty()){
            subStr+=",";
        }
    }
    //split substr
    i=0;
    std::stringstream ss(subStr);
    string str;
    while (ss>>i){
        if(ss.peek()==','){
            ss.ignore();
            vec.push_back(str);
            str.clear();
        }else{
            str+=i ;
        }
    }
    return vec;
}