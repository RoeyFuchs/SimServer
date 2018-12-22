#ifndef SIMSERVER_EXPRESSION_H
#define SIMSERVER_EXPRESSION_H
#include <memory>
using namespace std;

class Expression {
public:
    virtual double Execute() = 0;
};

#endif //SIMSERVER_EXPRESSION_H
