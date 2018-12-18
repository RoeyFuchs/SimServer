//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_UTILS_H
#define SIMSERVER_UTILS_H

#include "../Expression/ConditionExpression.h"
#include <vector>
#include <string>
class Utils {
private:
    std::vector <std::string> operators={">","<","==","!=",">=","<="};
public:
    /**
 * Slice
 * @tparam T
 * @param vec
 * @param beginIndex
 * @param endIndex
 * @return sub vector according to given indexes
 */
    template <typename T>
    std::vector<T> Slice (std::vector<T> &vec, int beginIndex, int endIndex){
        //copy data to sub vector
        std::vector<T> subVector(endIndex-beginIndex+1);
        std::copy(vec.begin()+beginIndex,vec.begin()+endIndex+1, subVector.begin());
        return subVector;
    }

/**
 * GetConditionOperatorPosition
 * @param tokens
 * @return index
 * The function search for operator condition position and return its index
 */
int GetConditionOperatorPosition(std::vector<std::string> &tokens){
    for (int i = 0; i < tokens.size(); ++i) {
        for (int j = 0; j <operators.size() ; ++j) {
            if(tokens[i]==operators[j]){
                return i;
            }
        }
    }

    //TODO should it trow run time error?
    //throw runtime_error("No condition operator found at condition command");
}
};

#endif //SIMSERVER_UTILS_H
