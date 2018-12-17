//
// Created by stav on 12/16/18.
//

#ifndef SIMSERVER_UTILS_H
#define SIMSERVER_UTILS_H


#include <vector>

class Utils {
public:
    template <typename T>
    std::vector<T> Slice (std::vector<T> &v, int beginIndex, int endIndex);
};


#endif //SIMSERVER_UTILS_H
