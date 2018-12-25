#include <iostream>
#include "Expression/Number.h"

using namespace std;

#include "vector"
#include "Expression/MathExpression/Plus.h"
#include "Expression/MathExpression/Minus.h"
#include "Expression/MathExpression/Mult.h"
#include "Expression/MathExpression/Mult.h"
#include "Expression/MathExpression/Div.h"
#include "Tests/UtilsTester.h"
#include "Tests/ParserTests.h"
#include "Tests/NumberTest.h"
#include "Tests/ShuntinYardTests.h"
#include "Expression/ShuntingYard.h"
#include <stack>
#include "Utils/Utils.h"

int main() {

   /*shared_ptr<ConnectExpression> A = make_shared<ConnectExpression>("10.0.2.2", make_shared<Number>(5402));
   A->Execute();*/
  RunParserTests();


}