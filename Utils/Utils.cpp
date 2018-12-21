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
    int isPreviousExpIsNumber=this->IsNumber(tokens[0])||this->IsVar(tokens[0]);
    for(int i=1;i<tokens.size();i++){
        int isCurrentExpIsNumber= this->IsNumber(tokens[i])||this->IsVar(tokens[i]);
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
    return regex_match(s,std::regex("^(0|([1-9][0-9]*))(\\.[0-9]+)?$"));
}
/**
 * IsVar
 * @param s
 * @return true if the function is var or false otherwise
 */
bool Utils::IsVar(const std::string &s) {
    if((*this->varExpressionTable).find(s)==(*this->varExpressionTable).end()) {
        return false;
    }
    return true;
}
/**
* Slice
* @tparam T
* @param vec
* @param beginIndex
* @param endIndex
* @return sub vector according to given indexes
*/
std::vector<std::string> Utils::Slice(std::vector<std::string> myVec, int beginIndex, int endIndex) {
    std::vector<std::string> newVec;
    for (int i = beginIndex; i <= endIndex ; ++i) {
        newVec.push_back(myVec[i]);
    }
    return newVec;

}
/**
 * the function create map between the number of the line and that value,
 * of the xml file
 * @return a map
 */
std::map<int, std::string> Utils::GetXmlOrder() {
    std::map<int, std::string> newMap;
    std::ifstream myFile(XML_ORDER_FILE);
    if(!myFile.is_open()) {
        throw std::runtime_error(std::string("can't open XML file"));
    }
    int i = 0;
    std::string line;
    while(getline(myFile, line)) {
        newMap[i] = line;
        ++i;
    }
    myFile.close();
    return newMap;
}

std::vector<std::string> Utils::splitByChar(char *phrase, std::string delimiter){
    std::vector<std::string> list;
    std::string s = std::string(phrase);
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}