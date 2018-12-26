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
    char space =' ';
    int i=0;
    for(int i=0; i<line.size();i++){
        if((line[i]==space&& !concatString.empty())){
            concatString+=",";
        }else if(this->IsMathOperators(line[i])||
                (line[i]=='='&& !IsConditionOperator(line[i+1])&&
                 !IsConditionOperator(concatString[concatString.length()-1]))){
            concatString+=",";
            concatString+=line[i];
            concatString+=",";
        } else  if(line[i]!= space){
            concatString+=line[i];
        }
    }
    return concatString;
}
/**
 * ConvertStringToVector
 * @param line
 * @return vector of seperated string
 */
vector<string> Lexer::ConvertStringToVector(string line) {
    vector<string> vec;
    int k=0;
    while (k<line.size()) {
        string str;
        while (line[k]!=','&&k<line.size()){
            str+=line[k];
            k++;
        }
        if(str.length()>0) {
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
vector<string> Lexer::SeparateLine(string line) {
    string seperatedLine=this->SeparateLineByComma(line);
    return this->ConvertStringToVector(seperatedLine);
}