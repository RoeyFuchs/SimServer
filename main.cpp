#include <iostream>
#include "Expression/Number.h"

using namespace std;

#include "vector"
#include "Expression/MathExpression/Plus.h"
#include "Expression/MathExpression/Minus.h"
#include "Expression/MathExpression/Mult.h"
#include "Expression/MathExpression/Mult.h"
#include "Expression/MathExpression/Div.h"
#include "Tests/NumberTest.h"
#include "Expression/ShuntingYard.h"

int main() {
   cout << "Hello World :)" << endl;


   ShuntingYard A;
   string a = "5";
   cout << A.isNumber(a) << endl;


}