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
};

ConditionExpression CreateConditionExpression(std::vector<std::string> &tokens){

}


#endif //SIMSERVER_UTILS_H
