//
// Created by stav on 12/19/18.
//

#ifndef SIMSERVER_SUBVECTORBYITSEXPRESSION_H
#define SIMSERVER_SUBVECTORBYITSEXPRESSION_H

#include <vector>
#include <map>
#include "string"

class SubVectorByItsExpression {
private:
    std::map<std::string, int>expressionArguments;
public:
    SubVectorByItsExpression(std::map<std::string, int>expressionArguments){
        this->expressionArguments= expressionArguments;
    }
    template<typename T>
    std::vector<T> Slice(std::vector<T> &vec, int beginIndex, int endIndex) {
        //copy data to sub vector
        std::vector<T> subVector(endIndex - beginIndex + 1);
        std::copy(vec.begin() + beginIndex, vec.begin() + endIndex + 1, subVector.begin());
        return subVector;
    }

    std::vector<std::string> SubVarBindExp(std::vector<std::string> &tokens);

};


#endif //SIMSERVER_SUBVECTORBYITSEXPRESSION_H
