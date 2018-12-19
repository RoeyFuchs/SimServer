//
// Created by stav on 12/16/18.
//

#include <stdexcept>
#include <algorithm>
#include "Utils.h"
/**
 * GetConditionOperatorPosition
 * @param tokens
 * @return index
 * The function search for operator condition position and return its index
 */
int Utils::GetConditionOperatorPosition(std::vector<std::string> &tokens) {
    for (int i = 0; i < tokens.size(); ++i) {
        for (int j = 0; j <operators.size() ; ++j) {
            if(tokens[i]==operators[j]){
                return i;
            }
        }
    }
    throw std::runtime_error("No condition operator found at condition command");
}
/**
 * GetPositionsOfExpressions
 * @param tokens
 * @return int vector with expression indexes
 */
std::vector<int> Utils::GetPositionsOfExpressions(std::vector<std::string> &tokens) {
    std::vector<int> expressionsPositions;
    //first element in vector is also an expression
    expressionsPositions.push_back(0);
    int isPreviousExpIsNumber=this->IsNumber(tokens[0]);
    for(int i=1;i<tokens.size();i++){
        int isCurrentExpIsNumber= this->IsNumber(tokens[i]);
        //check for two consecutive numbers
        if(isCurrentExpIsNumber&&isPreviousExpIsNumber){
            expressionsPositions.push_back(i);
        }
        isPreviousExpIsNumber=isCurrentExpIsNumber;
    }
    return expressionsPositions;
}
/**
 * IsNumber
 * @param s
 * @return true if the string is a number or false otherwise
 */
bool Utils::IsNumber(const std::string &s) {
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}